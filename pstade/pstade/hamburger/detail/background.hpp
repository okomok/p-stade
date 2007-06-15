#ifndef PSTADE_HAMBURGER_DETAIL_BACKGROUND_HPP
#define PSTADE_HAMBURGER_DETAIL_BACKGROUND_HPP


// PStade.Hamburger
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/optional/optional.hpp>
#include <pstade/gravy/rgb.hpp>
#include <pstade/gravy/sdk/windows.hpp>
#include <pstade/tomato/wtl/gdi.hpp> // CBrush
#include "../graphics.hpp"
#include "../rectangle.hpp"
#include "../view_attributes.hpp"


namespace pstade { namespace hamburger { namespace detail {


    template< class Node >
    void paint_background(Node& node, graphics g, rectangle const& rc)
    {
        boost::optional<COLORREF> clr = gravy::rgb(node%Name_backgroundColor);
        if (!clr)
            return;

        WTL::CBrush br(::CreateSolidBrush(*clr));
        ::FillRect(g, rc, br);
    }


} } } // namespace pstade::hamburger::detail


#endif
