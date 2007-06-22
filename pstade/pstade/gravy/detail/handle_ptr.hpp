#ifndef PSTADE_GRAVY_DETAIL_HANDLE_PTR_HPP
#define PSTADE_GRAVY_DETAIL_HANDLE_PTR_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/operators.hpp> // totally_ordered
#include <pstade/contract.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/is_convertible.hpp>
#include <pstade/radish/bool_testable.hpp>
#include "../sdk/windows.hpp" // NULL


namespace pstade { namespace gravy { namespace detail {


    template<class T>
    struct handle_ptr_super
    {
        typedef
            radish::bool_testable  < T,
            boost::totally_ordered1< T
            > >
        type;
    };


    template<class Handle, class Assertion>
    struct handle_ptr :
        handle_ptr_super< handle_ptr<Handle, Assertion> >::type
    {
    private:
        typedef handle_ptr self_t;

    public:
        /*implicit*/ handle_ptr(Handle handle = NULL) :
            m_handle(handle)
        {
            PSTADE_CONSTRUCTOR_PRECONDITION (~
            )
        }

        template<class X> // for 'WTL::CHandleXXX' etc
        handle_ptr(X const& x, typename enable_if< is_convertible<X, Handle> >::type = 0) :
            m_handle(x)
        {
            PSTADE_CONSTRUCTOR_PRECONDITION (~
            )
        }

        Handle get() const
        {
            PSTADE_PUBLIC_PRECONDITION (~
            )

            return m_handle;
        }

        Handle operator *() const
        {
            PSTADE_PUBLIC_PRECONDITION (
                (::IsWindow(m_handle))
            )

            return m_handle;
        }

        operator radish::safe_bool() const
        {
            PSTADE_PUBLIC_PRECONDITION (~
            )

            return radish::make_safe_bool(m_handle != NULL);
        }

    // totally_ordered
        bool operator< (self_t const& other) const
        {
            PSTADE_PUBLIC_PRECONDITION (~
            )

            return m_handle < other.m_handle;
        }

        bool operator==(self_t const& other) const
        {
            PSTADE_PUBLIC_PRECONDITION (~
            )

            return m_handle == other.m_handle;
        }

    private:
        Handle m_handle;

        PSTADE_CLASS_INVARIANT
        (
            (m_handle != NULL ? Assertion()(m_handle) : true)
        )
    };


} } } // namespace pstade::gravy::detail


#endif
