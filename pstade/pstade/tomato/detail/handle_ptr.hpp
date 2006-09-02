#ifndef PSTADE_TOMATO_DETAIL_HANDLE_PTR_HPP
#define PSTADE_TOMATO_DETAIL_HANDLE_PTR_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/operators.hpp> // totally_ordered
#include <pstade/apple/sdk/windows.hpp> // NULL
#include <pstade/contract.hpp>
#include <pstade/radish/bool_testable.hpp>


namespace pstade { namespace tomato { namespace detail {


namespace handle_ptr_detail {


    template< class T >
    struct super_
    {
        typedef
            radish::bool_testable < T,
            boost::totally_ordered< T
            > >
        type;
    };


} // namespace handle_ptr_detail


template< class Handle, class Assertion >
struct handle_ptr :
    handle_ptr_detail::super_< handle_ptr<Handle, Assertion> >::type
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


} } } // namespace pstade::tomato::detail


#endif
