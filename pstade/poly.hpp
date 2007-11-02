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
// Q * is Convertible to O *.
// Q can be optionally Clonable.
//   (http://www.boost.org/libs/ptr_container/doc/reference.html#the-clonable-concept)


// Note:
//
// clone_ptr vs poly
//   clone_ptr is lightweight swappable.
//   poly can be lightweight copyable.


#include <cstddef> // size_t
#include <typeinfo>
#include <boost/assert.hpp>
#include <boost/mpl/size_t.hpp>
#include <boost/none.hpp>
#include <boost/operators.hpp> // totally_ordered1
#include <boost/type_traits/aligned_storage.hpp>
#include <boost/utility/compare_pointees.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/implicitly_defined.hpp>
#include <pstade/is_convertible.hpp>
#include <pstade/mpl_min_max.hpp>
#include <pstade/nullptr.hpp>
#include <pstade/radish/bool_testable.hpp>
#include <pstade/radish/value_pointable.hpp>
#include <pstade/reset_assignment.hpp>
#include <pstade/type_equal_to.hpp>
#include "./detail/clonable.hpp"
#include "./detail/pointer_cast.hpp"
#include "./poly_fwd.hpp"


namespace pstade {


    template<class O>
    struct poly_storage_size :
        mpl_min_c<std::size_t,
            PSTADE_POLY_MAX_STORAGE_SIZE,
            mpl_max_c<std::size_t, PSTADE_POLY_MIN_STORAGE_SIZE, sizeof(O)*2>::value
        >
    { };

    template<>
    struct poly_storage_size<void> :
        boost::mpl::size_t<PSTADE_POLY_MIN_STORAGE_SIZE>
    { };


    namespace poly_detail {


        namespace here = poly_detail;


        template<class O>
        union storage
        {
            O *ptr;
            mutable typename boost::aligned_storage<poly_storage_size<O>::value>::type buf_;

            void *address() const { return &buf_; }
        };


        template<class O, class Q>
        struct stores_locally :
            boost::mpl::bool_<sizeof(Q) <= poly_storage_size<O>::value>
        { };


        template<class O>
        struct virtual_
        {
            typedef void (*destory_type)(storage<O> &stg);
            typedef void (*copy_type)(storage<O> const &stg, storage<O> &to);
            typedef O *(*get_type)(storage<O> const &stg);
            typedef std::type_info const &(*typeid_type)();
        };


        template<class O, class Q>
        struct override_typeid
        {
            static std::type_info const &typeid_()
            {
                return typeid(Q);
            }
        };

        // local
        template<class O, class Q, bool = stores_locally<O, Q>::value>
        struct override_ :
            override_typeid<O, Q>
        {
            static void destroy(storage<O> &stg)
            {
                reinterpret_cast<Q *>(stg.address())->~Q();
            }

            static void copy(storage<O> const &stg, storage<O> &to)
            {
                Q const *q = reinterpret_cast<Q const *>(stg.address());
                new (to.address()) Q(*q);
            }

            static O *get(storage<O> const &stg)
            {
                return reinterpret_cast<Q *>(stg.address());
            }
        };

        // heap
        template<class O, class Q>
        struct override_<O, Q, false> :
            override_typeid<O, Q>
        {
            static void destroy(storage<O> &stg)
            {
                BOOST_ASSERT(stg.ptr);
                detail::clonable_delete(detail::pointer_cast<Q>(stg.ptr));
            }

            static void copy(storage<O> const &stg, storage<O> &to)
            {
                BOOST_ASSERT(stg.ptr);
                Q const *q = detail::pointer_cast<Q const>(stg.ptr);
                to.ptr = detail::clonable_new(*q);
            }

            static O *get(storage<O> const &stg)
            {
                BOOST_ASSERT(stg.ptr);
                return stg.ptr;
            }
        };


        // This must be pod for static-initialization.
        template<class O>
        struct vtable
        {
            typename virtual_<O>::destory_type destroy;
            typename virtual_<O>::copy_type copy;
            typename virtual_<O>::get_type get;
            typename virtual_<O>::typeid_type typeid_;
        };


        template<class O, class Q> inline
        vtable<O> const *vtable_pointer()
        {
            static vtable<O> const vtbl = {
                &override_<O, Q>::destroy,
                &override_<O, Q>::copy,
                &override_<O, Q>::get,
                &override_<O, Q>::typeid_
            };

            return &vtbl;
        }


        template<class O, class Q> inline
        void construct(storage<O> &stg, Q const &q, typename enable_if< stores_locally<O, Q> >::type = 0)
        {
            new (stg.address()) Q(q);
        }

        template<class O, class Q> inline
        void construct(storage<O> &stg, Q const &q, typename disable_if<stores_locally<O, Q> >::type = 0)
        {
            stg.ptr = detail::clonable_new(q);
        }


        template<class O, class Injector>
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
                m_pvtbl = vtable_pointer<O, Q>();
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
                m_pvtbl = vtable_pointer<O, Q>(); // nothrow
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
                stores_locally<O, Q>
            { };

        protected:
            O *get_() const
            {
                BOOST_ASSERT(!empty());
                return m_pvtbl->get(m_stg);
            }

        private:
            storage<O> m_stg;
            vtable<O> const *m_pvtbl;

            void destruct_() // nothrow
            {
                if (!empty())
                    m_pvtbl->destroy(m_stg);
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
            return type_equal_to(this->type(), typeid(Q));
        }

        template<class Q>
        Q &content()
        {
            BOOST_ASSERT(contains<Q>());
            return *detail::pointer_cast<Q>(this->get_());
        }

        template<class Q>
        Q const &content() const
        {
            BOOST_ASSERT(contains<Q>());
            return *detail::pointer_cast<Q const>(this->get_());
        }

    // totally_ordered
        bool operator< (self_t const &other) const
        {
            return boost::less_pointees(*this, other);
        }

        bool operator==(self_t const &other) const
        {
            return boost::equal_pointees(*this, other);
        }

    // workaround
        PSTADE_IMPLICITLY_DEFINED_COPY_TO_BASE(poly, super_t)
    };


} // namespace pstade


// Dereferenceable extension
//

#include <pstade/egg/extension.hpp>


namespace pstade_egg_extension {


    template<class O>
    struct Dereferenceable< pstade::poly<O> >
    {
        typedef O &reference;
    };

    template<class O>
    struct Dereferenceable< pstade::poly<O> const >
    {
        typedef O const &reference;
    };

    template< >
    struct Dereferenceable< pstade::poly<void> >
    {
        typedef void reference;
    };

    template< >
    struct Dereferenceable< pstade::poly<void> const >
    {
        typedef void reference;
    };


} // namespace pstade_egg_extension


#endif
