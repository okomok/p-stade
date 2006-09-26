#ifndef PSTADE_HAMBURGER_SUBVIEW_HPP
#define PSTADE_HAMBURGER_SUBVIEW_HPP


// PStade.Hamburger
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/windows.hpp>
#include <pstade/ketchup/core.hpp>
#include <pstade/oven/sort_range.hpp>
#include <pstade/statement.hpp>
#include <pstade/tomato/rgb.hpp>
#include "./detail/background.hpp"
#include "./detail/chain_mouse_message.hpp"
#include "./detail/layout.hpp"
#include "./element.hpp"
#include "./factory.hpp"
#include "./location.hpp"
#include "./view_attributes.hpp"
#include "./z_order.hpp"


namespace pstade { namespace hamburger {


    namespace subview_detail {


        template< class Node >
        void set_default_values(Node& node)
        {
            node%Name_backgroundColor           = Value_none;
            node%Name_backgroundImageHueShift   = "0.0";
            node%Name_backgroundImageSaturation = "1.0";
            node%Name_backgroundTiled           = Value_false;
            node%Name_resizeBackgroundImage     = Value_false;
        }


    } // namespace subview_detail


    struct subview :
        ketchup::message_processor<subview, element>
    {
        subview()
        {
            subview_detail::set_default_values(*this);
        }

        void override_set_bounds(rectangle const& rc)
        {
            m_bounds = rc;
            detail::layout(*this);
        }

        rectangle override_bounds() const
        {
            return m_bounds;
        }

        void override_paint(graphics g, rectangle const& rc)
        {
            detail::paint_background(*this, g, rc);

            BOOST_FOREACH (element& child, m_self/*|oven::sorted(z_order)*/) {
                child.paint(g, child.bounds() + rc.TopLeft());
            }
        }

        begin_msg_map
        <
            detail::chain_mouse_message<>,
            empty_entry<>
        >
        end_msg_map;

    private:
        rectangle m_bounds;
    };


    namespace subview_detail {


        PSTADE_STATEMENT(Register,
            hamburger::register_element<subview>("subview");
        )


    } // namespace subview_detail


} } // namespace pstade::hamburger


#endif
