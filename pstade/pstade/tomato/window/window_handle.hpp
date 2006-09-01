#ifndef PSTADE_TOMATO_WINDOW_WINDOW_HANDLE_HPP
#define PSTADE_TOMATO_WINDOW_WINDOW_HANDLE_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/windows.hpp> // HWND
#include <pstade/contract.hpp>
#include <pstade/radish/bool_testable.hpp>


namespace pstade { namespace tomato {


struct window_handle :
    private radish::bool_testable<window_handle>
{
    /*implicit*/ window_handle(HWND hWnd = NULL) :
        m_hWnd(hWnd)
    {
        PSTADE_CONSTRUCTOR_PRECONDITION (
        ~)    
    }

    HWND get() const
    {
        PSTADE_PUBLIC_PRECONDITION (
        ~)

        return m_hWnd;
    }

    HWND operator *() const
    {
        PSTADE_PUBLIC_PRECONDITION (
            (::IsWindow(m_hWnd))
        )

        return m_hWnd;
    }

    operator radish::safe_bool() const
    {
        PSTADE_PUBLIC_PRECONDITION (
        ~)

        return radish::make_safe_bool(m_hWnd != NULL);
    }

private:
    HWND m_hWnd;

    PSTADE_CLASS_INVARIANT
    (
        (m_hWnd ? ::IsWindow(m_hWnd) : true)
    )
};


} } // namespace pstade::tomato


#endif
