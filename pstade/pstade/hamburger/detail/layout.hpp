#ifndef PSTADE_HAMBURGER_DETAIL_LAYOUT_HPP
#define PSTADE_HAMBURGER_DETAIL_LAYOUT_HPP


// PStade.Hamburger
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/foreach.hpp>
#include <pstade/oven/equals.hpp>
#include "../dimension.hpp"
#include "../element.hpp"
#include "../size.hpp"


namespace pstade { namespace hamburger { namespace detail {


    namespace layout_detail {


        inline
        rectangle att_bounds(element& elem)
        {
            try {
                int l = pstade::lexical(elem%Name_left);
                int t = pstade::lexical(elem%Name_top);
                int w = pstade::lexical(elem%Name_width);
                int h = pstade::lexical(elem%Name_height);
                return rectangle(l, t, l+w, t+h);
            }
            catch (boost::bad_lexical_cast const&) {
                return rectangle(0, 0, 0, 0);
            }
        }


    } // namespace layout_detail


    inline
    void layout(element& parent)
    {
        dimension paAttSize = layout_detail::att_bounds(parent).Size();
        dimension paSize = hamburger::size(parent);

        BOOST_FOREACH (element& child, parent) {

            rectangle chAttBounds = layout_detail::att_bounds(child);
            rectangle result;

            if (oven::equals(child%Name_horizontalAlignment, Value_left)) {
                result.left  = chAttBounds.left;
                result.right = chAttBounds.right;
            }
            else if (oven::equals(child%Name_horizontalAlignment, Value_right)) {
                result.right = paSize.cx - (paAttSize.cx - chAttBounds.right);
                result.left  = result.right - chAttBounds.Width();
            }
            else if (oven::equals(child%Name_horizontalAlignment, Value_center)) {
                int d = (paSize.cx - chAttBounds.Width())/2;
                result.left  = d;
                result.right = d + chAttBounds.Width();
            }
            else if (oven::equals(child%Name_horizontalAlignment, Value_stretch)) {
                result.left  = chAttBounds.left;
                result.right = paSize.cx - (paAttSize.cx - chAttBounds.right);
            }
            else {
                BOOST_ASSERT(false);
                return;
            }

            if (oven::equals(child%Name_verticalAlignment, Value_top)) {
                result.top    = chAttBounds.top;
                result.bottom = chAttBounds.bottom;
            }
            else if (oven::equals(child%Name_verticalAlignment, Value_bottom)) {
                result.bottom = paSize.cy - (paAttSize.cy - chAttBounds.bottom);
                result.top    = result.bottom - chAttBounds.Height();
            }
            else if (oven::equals(child%Name_verticalAlignment, Value_center)) {
                int d = (paSize.cy - chAttBounds.Height())/2;
                result.top    = d;
                result.bottom = d + chAttBounds.Height();
            }
            else if (oven::equals(child%Name_verticalAlignment, Value_stretch)) {
                result.top    = chAttBounds.top;
                result.bottom = paSize.cy - (paAttSize.cy - chAttBounds.bottom);
            }
            else {
                BOOST_ASSERT(false);
                return;
            }

            child.set_bounds(result);

        } // BOOST_FOREACH
    }


} } } // namespace pstade::hamburger::detail


#endif
