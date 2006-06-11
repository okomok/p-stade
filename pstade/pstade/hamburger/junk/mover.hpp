#ifndef PSTADE_HAMBURGER_MOVER_HPP
#define PSTADE_HAMBURGER_MOVER_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/lambda/bind.hpp>
#include <boost/lambda/core.hpp> // _1
#include <pstade/apple/atl/win.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/if_debug.hpp>
#include <pstade/instance.hpp>
#include <pstade/ketchup/core.hpp>
#include <pstade/lime/find.hpp>
#include <pstade/napkin/dout.hpp>
#include <pstade/napkin/nout.hpp>
#include <pstade/napkin/ostream.hpp>
#include <pstade/oven/equal.hpp>
#include <pstade/statement.hpp>
#include <pstade/tomato/get.hpp>
#include "./element.hpp"
#include "./factory.hpp"
#include "./hwnd.hpp"
#include "./line.hpp"
#include "./point.hpp"
#include "./rectangle.hpp"
#include "./size.hpp"
#include "./to_screen_to.hpp"


namespace pstade { namespace hamburger {


namespace mover_detail {


    PSTADE_IF_DEBUG (
        PSTADE_INSTANCE(napkin::ostream, os, value)
    )


    inline
    line filter(line next, line pa)
    {
        int d1 = pa.begin() - next.end(); // distance(next.end(), pa.begin());
        if (d1 >= 0)
            next += d1+1;

        int d2 = next.begin() - pa.end(); // distance(pa.end(), next.begin());
        if (d2 >= 0)
            next -= d2+1;

        return next;
    }


    inline
    rectangle filter(rectangle next, rectangle pa)
    {
        line horznext = hamburger::make_horizontal(next);
        line horzpa   = hamburger::make_horizontal(pa);

        line vertnext = hamburger::make_vertical(next);
        line vertpa   = hamburger::make_vertical(pa);

        return hamburger::make_rectangle(
            mover_detail::filter(horznext, horzpa),
            mover_detail::filter(vertnext, vertpa)
        );
    }


    PSTADE_INSTANCE(const ustring, Name_target, ("target"))


} // namespace mover_detail


struct mover :
    ketchup::message_processor<mover,
        ATL::CWindowImpl<mover>,
        element
    >
{
    explicit mover()
    {        
        PSTADE_IF_DEBUG (
            mover_detail::os.reset(napkin::dout);
        )
    }

protected:
    void override_create()
    {
        namespace bll = boost::lambda;
        m_target = lime::find_up(*this, bll::bind(&mover::is_target, this, bll::_1));
    }

    void override_set_bounds(rectangle rc)
    {
        m_bounds = rc;
    }

    rectangle override_bounds() const
    {
        return m_bounds;
    }

private:
friend class ketchup::access;
    void on_lbuttondown(UINT uFlags, point pt)
    {
        if (!m_target)
            return;

        PSTADE_REQUIRE(SubclassWindow(hamburger::hwnd(*m_target)));
        pt = hamburger::to_screen(*this, pt);

        SetCapture();
        m_marker = pt;
        m_targetBounds = (*m_target).bounds();

        pstade::unused(uFlags);
    }

    void on_lbuttonup(UINT uFlags, point pt)
    {
        if (!is_capturing()) {
            set_msg_handled(false);
            return;
        }

        BOOST_ASSERT(m_target);

        move(pt);
        ReleaseCapture();
        UnsubclassWindow();

        pstade::unused(uFlags);
    }

    void on_mousemove(UINT uFlags, point pt)
    {
        if (!is_capturing()) {
            set_msg_handled(false);
            return;
        }

        BOOST_ASSERT(m_target);

        move(pt);

        pstade::unused(uFlags);
    }

    LRESULT on_nchittest(point pt)
    {
        return HTCAPTION;
        pstade::unused(pt);
    }

    begin_msg_map
    <
        /*
        msg_wm_mousemove<&_::on_mousemove>,
        msg_wm_lbuttonup<&_::on_lbuttonup>,
        msg_wm_lbuttondown<&_::on_lbuttondown>,
        */
        msg_wm_nchittest<&_::on_nchittest>,
        empty_entry<>
    >
    end_msg_map;

private:
    rectangle m_bounds;
    boost::optional<element&> m_target;
    point m_marker;
    rectangle m_targetBounds;

    void move(point pt)
    {
        // pt is on a window
        ClientToScreen(&pt);

        rectangle next(m_targetBounds);
        next += (pt - m_marker);
        (*m_target).set_bounds(next);

        /*
        rectangle rcpa = hamburger::desktop_bounds(*this);
        rectangle result = mover_detail::filter(next, rcpa);
        BOOST_ASSERT(!(rcpa & result).IsRectEmpty());
        (*m_target).set_bounds(result);
        */
    }

    bool is_capturing() const
    {
        return m_hWnd != NULL;
    }

    bool is_target(element& elem)
    {
        return oven::equals(elem%Name_id, *this%mover_detail::Name_target);
    }
};


namespace mover_detail {


    PSTADE_STATEMENT(Register,
        hamburger::register_element<mover>("mover");
    )


} // namespace mover_detail


} } // namespace pstade::hamburger


#endif
