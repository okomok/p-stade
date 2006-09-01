#ifndef PSTADE_TOMATO_WINDOW_REF_HPP
#define PSTADE_TOMATO_WINDOW_REF_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/nonassignable.hpp>


namespace pstade { namespace tomato {


struct window_ref :
    private nonassignable
{
    /*implicit*/ window_ref(HWND hWnd) :
        m_hWnd(hWnd)
    {
        BOOST_ASSERT(::IsWindow(m_hWnd));
    }

    operator HWND() const
    {
        BOOST_ASSERT(::IsWindow(m_hWnd));
        return m_hWnd;
    }

    HWND get() const
    {
        BOOST_ASSERT(::IsWindow(m_hWnd));
        return m_hWnd;
    }

private:
    HWND m_hWnd;
};


} } // namespace pstade::tomato


#endif
