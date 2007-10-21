#ifndef PSTADE_POLY_HPP
#define PSTADE_POLY_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// Boost.Function
// Boost.Optional
// http://homepages.fh-regensburg.de/~mpool/mpool07/proceedings/5.pdf


// Preconditions:
//
// Q is CopyConstructible.
// Q& is Convertible to O&.
// Q is Clonable.
//   (http://www.boost.org/libs/ptr_container/doc/reference.html#the-clonable-concept)


// Note:
//
// clone_ptr vs poly
//   clone_ptr is lightweight swappable.
//   poly can be lightweight copyable.


#include <typeinfo>
#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/none.hpp>
#include <boost/operators.hpp> // totally_ordered1
#include <boost/ptr_container/clone_allocator.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/utility/compare_pointees.hpp>
#include <pstade/egg/static_downcast.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/implicitly_defined.hpp>
#include <pstade/is_convertible.hpp>
#include <pstade/make_bool.hpp>
#include <pstade/nullptr.hpp>
#include <pstade/radish/bool_testable.hpp>
#include <pstade/radish/value_pointable.hpp>
#include <pstade/reset_assignment.hpp>


namespace pstade {


    template<class O>
    struct poly;


    // specializable traits
    template<class O>
    struct poly_storage_size :
        boost::mpl::size_t< sizeof(O) * 2 > // do you know better size?
    { };


    namespace poly_detail {


        namespace here = poly_detail;


        template<class O> inline
        O *new_(O const &o)
        {
            return boost::heap_clone_allocator::allocate_clone(o);
        }

        template<class O> inline
        void delete_(O *ptr)
        {
            return boost::heap_clone_allocator::deallocate_clone(ptr);
        }


        template<class O>
        union storage
        {
            O *ptr;
            mutable char data_[poly_storage_size<O>::value];

            void *data() const { return &data_[0]; }
        };


        template<class O, class Q>
        struct is_locally_storable_aux :
            boost::mpl::bool_<
                (sizeof(Q) <= sizeof(storage<O>)) &&
                (boost::alignment_of< storage<O> >::value % boost::alignment_of<Q>::value == 0)
            >
        { };

        template<class O, class Q>
        struct is_locally_storable :
            is_locally_storable_aux<O, typename boost::remove_cv<Q>::type>
        { };


        template<class O>
        struct virtual_destroy
        {
            typedef void (*type)(storage<O> &stg);
        };

        template<class O, class Q>
        struct override_destroy
        {
            static void call(storage<O> &stg)
            {
                aux(stg, is_locally_storable<O, Q>());
            }

        private:
            // local
            static void aux(storage<O> &stg, boost::mpl::true_)
            {
                reinterpret_cast<Q *>(stg.data())->~Q();
            }

            // heap
            static void aux(storage<O> &stg, boost::mpl::false_)
            {
                here::delete_(stg.ptr);
            }
        };


        template<class O>
        struct virtual_copy
        {
            typedef void (*type)(storage<O> const &stg, storage<O> &to);
        };

        template<class O, class Q>
        struct override_copy
        {
            static void call(storage<O> const &stg, storage<O> &to)
            {
                aux(stg, to, is_locally_storable<O, Q>());
            }

        private:
            // local
            static void aux(storage<O> const &stg, storage<O> &to, boost::mpl::true_)
            {
                Q const *q = reinterpret_cast<Q const *>(stg.data());
                new (to.data()) Q(*q);
            }

            // heap
            static void aux(storage<O> const &stg, storage<O> &to, boost::mpl::false_)
            {
                to.ptr = here::new_(*stg.ptr);
            }
        };


        template<class O>
        struct virtual_get
        {
            typedef O *(*type)(storage<O> const &stg);
        };

        template<class O, class Q>
        struct override_get
        {
            static O *call(storage<O> const &stg)
            {
                return aux(stg, is_locally_storable<O, Q>());
            }

        private:
            // local
            static O *aux(storage<O> const &stg, boost::mpl::true_)
            {
                return reinterpret_cast<Q *>(stg.data());
            }

            // heap
            static O *aux(storage<O> const &stg, boost::mpl::false_)
            {
                return stg.ptr;
            }
        };


        template<class O>
        struct virtual_typeid
        {
            typedef std::type_info const &(*type)();
        };

        template<class O, class Q>
        struct override_typeid
        {
            static std::type_info const &call()
            {
                return typeid(Q);
            }
        };


        template<class O>
        struct vtable
        {
            typename virtual_destroy<O>::type destroy;
            typename virtual_copy<O>::type    copy;
            typename virtual_get<O>::type     get;
            typename virtual_typeid<O>::type  typeid_;

            vtable()
            {
                reset();
            }

            template<class Q>
            void reset(Q const &)
            {
                destroy = &override_destroy<O, Q>::call;
                copy    = &override_copy<O, Q>::call;
                get     = &override_get<O, Q>::call;
                typeid_ = &override_typeid<O, Q>::call;
            }

            void reset()
            {
                destroy = PSTADE_NULLPTR;
                copy    = PSTADE_NULLPTR;
                get     = PSTADE_NULLPTR;
                typeid_ = PSTADE_NULLPTR;
            }

            bool is_empty() const
            {
                return !destroy;
            }
        };


        template<class O, class Q> inline
        void construct(storage<O> &stg, Q const &q, typename enable_if< is_locally_storable<O, Q> >::type = 0)
        {
            new (stg.data()) Q(q);
        }

        template<class O, class Q> inline
        void construct(storage<O> &stg, Q const &q, typename disable_if<is_locally_storable<O, Q> >::type = 0)
        {
            stg.ptr = here::new_(q);
        }


        template<class O, class Injector>
        struct impl :
            Injector
        {
        private:
            typedef impl self_t;

        public:
        // structors
            impl()
            { }

            template<class Q>
            explicit impl(Q const &q)
            {
                here::construct(m_stg, q);
                m_vtbl.reset(q);
            }

            impl(impl const &other)
            {
                if (!other.empty()) {
                    other.m_vtbl.copy(other.m_stg, m_stg);
                    m_vtbl = other.m_vtbl;
                }
            }

            ~impl()
            {
                destruct_();
            }

        // assignments
            impl &operator=(impl const &other) // basic
            {
                if (&other == this)
                    return *this;

                reset(); // nothrow

                if (!other.empty()) {
                    other.m_vtbl.copy(other.m_stg, m_stg); // maythrow
                    m_vtbl = other.m_vtbl; // nothrow
                }

                return *this;
            }

            void reset(boost::none_t = boost::none) // nothrow
            {
                destruct_(); // nothrow
                m_vtbl.reset(); // nothrow
            }

            template<class Q>
            void reset(Q const &q) // basic
            {
                reset(); // nothrow

                here::construct(m_stg, q); // maythrow
                m_vtbl.reset(q); // nothrow
            }

        // boost::any compatibles
            bool empty() const
            {
                return m_vtbl.is_empty();
            }

            std::type_info const &type() const
            {
                return !empty() ? m_vtbl.typeid_() : typeid(void);
            }

        protected:
            O *get_() const
            {
                BOOST_ASSERT(!empty());
                return m_vtbl.get(m_stg);
            }

        private:
            vtable<O> m_vtbl;
            storage<O> m_stg;

            void destruct_() // nothrow
            {
                if (!empty())
                    m_vtbl.destroy(m_stg);
            }
        };


        template<class O>
        struct super_
        {
            typedef
                impl<O,
                    radish::bool_testable  < poly<O>,
                    radish::value_pointable< poly<O>, O,
                    boost::totally_ordered1< poly<O> > > >
                >
            type;
        };

            
    } // namespace poly_detail


    template<class O>
    struct poly :
        poly_detail::super_<O>::type
    {
    private:
        typedef poly self_t;
        typedef typename poly_detail::super_<O>::type super_t;

    public:
    // structors
        poly(boost::none_t = boost::none)
        { }

        template<class Q>
        poly(Q const &q, typename enable_if< is_convertible<Q const &, O const &> >::type = 0) :
            super_t(q)
        { }

    // assignments
        PSTADE_RESET_ASSIGNMENT(poly)

    // bool_testable
        operator radish::safe_bool() const
        {
            return radish::make_safe_bool(!this->empty());
        }

    // value_pointable (const affects.)
        O *operator->()
        {
            return this->get_();
        }

        O const *operator->() const
        {
            return this->get_();
        }

    // content access
        template<class Q>
        bool contains() const
        {
            return make_bool(this->type() == typeid(Q));
        }

        template<class Q>
        Q &content()
        {
            BOOST_ASSERT(contains<Q>());
            return egg::static_downcast<Q>(*this->get_());
        }

        template<class Q>
        Q const &content() const
        {
            BOOST_ASSERT(contains<Q>());
            return egg::static_downcast<Q>(*this->get_());
        }

    // totally_ordered
        bool operator< (self_t const& other) const
        {
            return boost::less_pointees(*this, other);
        }

        bool operator==(self_t const& other) const
        {
            return boost::equal_pointees(*this, other);
        }

    // workaround
        PSTADE_IMPLICITLY_DEFINED_COPY_TO_BASE(poly, super_t)
    };


} // namespace pstade


#endif
