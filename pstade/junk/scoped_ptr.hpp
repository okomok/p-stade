#ifndef PSTADE_SCOPED_PTR_HPP
#define PSTADE_SCOPED_PTR_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <typeinfo>
#include <boost/assert.hpp>
#include <boost/operators.hpp> // totally_ordered1
#include <pstade/apple/auto_ptr_fwd.hpp>
#include <pstade/radish/pointable.hpp>
#include <pstade/type_equal_to.hpp>
#include "./detail/pointer_cast.hpp"
// #include "./scoped_ptr_fwd.hpp"


namespace pstade {


    namespace scoped_ptr_detail {


        template<class T>
        struct virtual_
        {
            typedef void (*delete_type)(T *p);
            typedef std::type_info const &(*typeid_type)();
        };


        template<class T, class U>
        struct override_<T, U>
        {
            static void delete_(T *p)
            {
                boost::checked_delete(detail::pointer_cast<U>(p));
            }

            static std::type_info const &typeid_()
            {
                return typeid(U);
            }
        };


        // This must be pod for static-initialization.
        template<class T>
        struct vtable
        {
            typename virtual_<T>::delete_type delete_;
            typename virtual_<T>::typeid_type typeid_;
        };


        template<class T, class U> inline
        vtable<T> const *vtable_pointer()
        {
            static vtable<T> const vtbl = {
                &override_<T, U>::destruct
                &override_<T, U>::typeid_
            };

            return &vtbl;
        }

            
    } // namespace scoped_ptr_detail


    template<class T>
    struct scoped_ptr :
        radish::pointable      < scoped_ptr<T>, T,
        boost::totally_ordered1< scoped_ptr<T> > >
    {
    private:
        typedef scoped_ptr this_t;

    public:
    // structors
        template<class U>
        explicit scoped_ptr(U *p) :
            m_ptr(p), m_pvtbl(scoped_ptr_detail::vtable_pointer<T, U>())
        { }

        template<class U>
        explicit scoped_ptr(std::auto_ptr<U> p) :
            m_ptr(p.release()), m_pvtbl(scoped_ptr_detail::vtable_pointer<T, U>())
        { }

        ~scoped_ptr()
        {
            BOOST_ASSERT(m_ptr);
            BOOST_ASSERT(m_pvtbl);
            m_pvtbl->destruct(m_ptr);
        }

    // pointable
        T *operator->() const
        {
            BOOST_ASSERT(m_ptr);
            return m_ptr;
        }

        Clonable *get() const
        {
            return m_ptr;
        }

    // totally_ordered
        bool operator< (this_t const &that) const
        {
            return m_ptr < that.m_ptr;
        }

        bool operator==(this_t const &that) const
        {
            return m_ptr == that.m_ptr;
        }

    // content access
        std::type_info const &type() const
        {
            return m_pvtbl->typeid_();
        }

        template<class U>
        bool contains() const
        {
            return type_equal_to(type(), typeid(U));
        }

        template<class U>
        U &content() const
        {
            BOOST_ASSERT(contains<U>());
            return *detail::pointer_cast<U>(get());
        }

    private:
        scoped_ptr(this_t const &that);
        scoped_ptr &operator=(this_t const &that);
    };


} // namespace pstade


// Dereferenceable extension
//

#include <pstade/egg/extension.hpp>


namespace pstade_egg_extension {


    template<class T>
    struct Dereferenceable< pstade::scoped_ptr<T> >
    {
        typedef T &reference;
    };

    template<class T>
    struct Dereferenceable< pstade::scoped_ptr<T> const >
    {
        typedef T &reference;
    };

    template< >
    struct Dereferenceable< pstade::scoped_ptr<void> >
    {
        typedef void reference;
    };

    template< >
    struct Dereferenceable< pstade::scoped_ptr<void> const >
    {
        typedef void reference;
    };


} // namespace pstade_egg_extension


#endif
