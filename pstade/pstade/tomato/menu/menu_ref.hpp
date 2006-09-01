#ifndef PSTADE_TOMATO_MENU_MENU_REF_HPP
#define PSTADE_TOMATO_MENU_MENU_REF_HPP


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


struct menu_ref :
    private nonassignable
{
    /*implicit*/ menu_ref(HMENU hWnd) :
        m_hMenu(hWnd)
    {
        BOOST_ASSERT(::IsMenu(m_hMenu));
    }

    operator HMENU() const
    {
        BOOST_ASSERT(::IsMenu(m_hMenu));
        return m_hMenu;
    }

    HMENU get() const
    {
        BOOST_ASSERT(::IsMenu(m_hMenu));
        return m_hMenu;
    }

private:
    HMENU m_hMenu;
};


} } // namespace pstade::tomato


#endif
