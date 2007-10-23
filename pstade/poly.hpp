#ifndef PSTADE_POLY_HPP
#define PSTADE_POLY_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Copyright (C) 2007, Corrado Zoccolo
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
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


#include <cstddef> // size_t
#include <typeinfo>
#include <boost/assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/none.hpp>
#include <boost/operators.hpp> // totally_ordered1
#include <boost/ptr_container/clone_allocator.hpp>
#include <boost/type_traits/aligned_storage.hpp>
#include <boost/utility/compare_pointees.hpp>
#include <pstade/egg/static_downcast.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/implicitly_defined.hpp>
#include <pstade/is_convertible.hpp>
#include <pstade/make_bool.hpp>
#include <pstade/mpl_min_max.hpp> // mpl_max_c
#include <pstade/nullptr.hpp>
#include <pstade/radish/bool_testable.hpp>
#include <pstade/radish/value_pointable.hpp>
#include <pstade/reset_assignment.hpp>
#include <pstade/use_default.hpp>
#include "./poly_fwd.hpp"


namespace pstade {


    template<class O>
    struct poly_storage_size :
        mpl_max_c<std::size_t, PSTADE_POLY_MIN_STORAGE_SIZE, sizeof(O)*2>
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


        template<class O, class Size>
        struct storage_size :
            if_use_default< Size, poly_storage_size<O> >::type
        { };

        template<class O, class Size>
        union storage
        {
            O *ptr;
            mutable typename boost::aligned_storage<storage_size<O, Size>::value>::type buf_;

            void *address() const { return &buf_; }
        };


        template<class O, class Size, class Q>
        struct stores_locally :
            boost::mpl::bool_<sizeof(Q) <= storage_size<O, Size>::value>
        { };


        template<class O, class Size>
        struct virtual_destroy
        {
            typedef void (*type)(storage<O, Size> &stg);
        };

        template<class O, class Size, class Q>
        struct override_destroy
        {
            static void call(storage<O, Size> &stg)
            {
                aux(stg, stores_locally<O, Size, Q>());
            }

        private:
            // local
            static void aux(storage<O, Size> &stg, boost::mpl::true_)
            {
                reinterpret_cast<Q *>(stg.address())->~Q();
            }

            // heap
            static void aux(storage<O, Size> &stg, boost::mpl::false_)
            {
                here::delete_(stg.ptr);
            }
        };


        template<class O, class Size>
        struct virtual_copy
        {
            typedef void (*type)(storage<O, Size> const &stg, storage<O, Size> &to);
        };

        template<class O, class Size, class Q>
        struct override_copy
        {
            static void call(storage<O, Size> const &stg, storage<O, Size> &to)
            {
                aux(stg, to, stores_locally<O, Size, Q>());
            }

        private:
            // local
            static void aux(storage<O, Size> const &stg, storage<O, Size> &to, boost::mpl::true_)
            {
                Q const *q = reinterpret_cast<Q const *>(stg.address());
                new (to.address()) Q(*q);
            }

            // heap
            static void aux(storage<O, Size> const &stg, storage<O, Size> &to, boost::mpl::false_)
            {
                to.ptr = here::new_(*stg.ptr);
            }
        };


        template<class O, class Size>
        struct virtual_get
        {
            typedef O *(*type)(storage<O, Size> const &stg);
        };

        template<class O, class Size, class Q>
        struct override_get
        {
            static O *call(storage<O, Size> const &stg)
            {
                return aux(stg, stores_locally<O, Size, Q>());
            }

        private:
            // local
            static O *aux(storage<O, Size> const &stg, boost::mpl::true_)
            {
                return reinterpret_cast<Q *>(stg.address());
            }

            // heap
            static O *aux(storage<O, Size> const &stg, boost::mpl::false_)
            {
                return stg.ptr;
            }
        };


        template<class O, class Size>
        struct virtual_typeid
        {
            typedef std::type_info const &(*type)();
        };

        template<class O, class Size, class Q>
        struct override_typeid
        {
            static std::type_info const &call()
            {
                return typeid(Q);
            }
        };


        // This must be pod for static-initialization.
        template<class O, class Size>
        struct vtable
        {
            typename virtual_destroy<O, Size>::type destroy;
            typename virtual_copy<O, Size>::type    copy;
            typename virtual_get<O, Size>::type     get;
            typename virtual_typeid<O, Size>::type  typeid_;
        };


        template<class O, class Size, class Q> inline
        vtable<O, Size> const *vtable_pointer()
        {
            static vtable<O, Size> const vtbl = { 
                &override_destroy<O, Size, Q>::call,
                &override_copy<O, Size, Q>::call,
                &override_get<O, Size, Q>::call,
                &override_typeid<O, Size, Q>::call
            };

            return &vtbl;
        }


        template<class O, class Size, class Q> inline
        void construct(storage<O, Size> &stg, Q const &q, typename enable_if< stores_locally<O, Size, Q> >::type = 0)
        {
            new (stg.address()) Q(q);
        }

        template<class O, class Size, class Q> inline
        void construct(storage<O, Size> &stg, Q const &q, typename disable_if<stores_locally<O, Size, Q> >::type = 0)
        {
            stg.ptr = here::new_(q);
        }


        template<class O, class Size, class Injector>
        struct impl :
            Injector
        {
        private:
            typedef impl self_t;

        public:
        // structors
            impl() :
              m_pvtbl(PSTADE_NULLPTR)
            { }

            template<class Q>
            explicit impl(Q const &q)
            {
                here::construct(m_stg, q);
                m_pvtbl = vtable_pointer<O, Size, Q>();
            }

            impl(self_t const &other) :
                m_pvtbl(PSTADE_NULLPTR)
            {
                if (!other.empty()) {
                    other.m_pvtbl->copy(other.m_stg, m_stg);
                    m_pvtbl = other.m_pvtbl;
                }
            }

            ~impl()
            {
                destruct_();
            }

        // assignments
            void reset(boost::none_t = boost::none) // nothrow
            {
                destruct_(); // nothrow
                m_pvtbl = PSTADE_NULLPTR; // nothrow
            }

            template<class Q>
            void reset(Q const &q) // basic
            {
                reset(); // nothrow

                here::construct(m_stg, q); // maythrow
                m_pvtbl = vtable_pointer<O, Size, Q>(); // nothrow
            }

            self_t &operator=(self_t const &other) // basic
            {
                if (&other == this)
                    return *this;

                reset(); // nothrow

                if (!other.empty()) {
                    other.m_pvtbl->copy(other.m_stg, m_stg); // maythrow
                    m_pvtbl = other.m_pvtbl; // nothrow
                }

                return *this;
            }

        // boost::any compatibles
            bool empty() const
            {
                return !m_pvtbl;
            }

            std::type_info const &type() const
            {
                return !empty() ? m_pvtbl->typeid_() : typeid(void);
            }

        // misc
            template<class Q>
            struct is_locally_stored :
                stores_locally<O, Size, Q>
            { };

        protected:
            O *get_() const
            {
                BOOST_ASSERT(!empty());
                return m_pvtbl->get(m_stg);
            }

        private:
            vtable<O, Size> const *m_pvtbl;
            storage<O, Size> m_stg;

            void destruct_() // nothrow
            {
                if (!empty())
                    m_pvtbl->destroy(m_stg);
            }
        };


        template<class O, class Size>
        struct super_
        {
            typedef
                impl<O, Size,
                    radish::bool_testable  < poly<O, Size>,
                    radish::value_pointable< poly<O, Size>, O,
                    boost::totally_ordered1< poly<O, Size> > > >
                >
            type;
        };

            
    } // namespace poly_detail


    template<class O, class Size>
    struct poly :
        poly_detail::super_<O, Size>::type
    {
    private:
        typedef poly self_t;
        typedef typename poly_detail::super_<O, Size>::type super_t;

    public:
    // structors
        poly(boost::none_t = boost::none)
        { }

        template<class Q>
        poly(Q const &q, typename enable_if< is_convertible<Q *, O *> >::type = 0) :
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
