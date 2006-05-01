#ifndef PSTADE_HAMBURGER_VIEW_HPP
#define PSTADE_HAMBURGER_VIEW_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/atl/win.hpp>
#include <boost/microsoft/wtl/frame.hpp> // CMessageFilter, CIdleHandler
#include <pstade/ketchup.hpp>
#include <pstade/lime/ustring.hpp>
#include "./element.hpp"


namespace pstade { namespace hamburger {


PSTADE_INSTANCE(const lime::ustring, view_name, ("view"))


namespace view_detail {


	template< class ViewT >
	struct super_
	{
		typedef ATL::CWindowImpl<
			ViewT,
			ATL::CWindow,
			ATL::CWinTraits<
				WS_OVERLAPPED|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
				WS_EX_APPWINDOW
			>
		> wnd_t;

		typedef ketchup::message_processor<ViewT,
			wnd_t
		> type;
	};


} // namespace view_detail


struct view :
	view_detail::super_<view>::type,
	element,
	WTL::CMessageFilter, WTL::CIdleHandler
{
private:
	typedef view_detail::super_<view>::type super_t;

public:
	// structors
	//
    explicit view(element_node& parent) :
        element(parent, view_name)
	{
		WTL::CRect rc(CW_USEDEFAULT, 0, 0, 0);
		Create(NULL, rc, 0, 0, 0);
	}

	// WTL
	//
	virtual BOOL OnIdle() {
		return FALSE;
	}

	virtual BOOL PreTranslateMessage(MSG* /*pMsg*/) {
		return FALSE;
	}

	// element_interface
	//
	virtual void set_bounds(rect)
	{
	}

	virtual rect get_bounds() const
	{
		return rect();
	}

	virtual void set_visible(bool v)
	{
		v;
	}

	virtual bool is_visible() const
	{
		return true;
	}

    begin_msg_map
    <
        empty_entry<>
    >
    end_msg_map;
};


PSTADE_INSTANCE(const lime::ustring, backgroundColor,			value)
PSTADE_INSTANCE(const lime::ustring, backgroundImage,			value)
PSTADE_INSTANCE(const lime::ustring, backgroundImageHueShift,	value)
PSTADE_INSTANCE(const lime::ustring, backgroundImageSaturation,	value)
PSTADE_INSTANCE(const lime::ustring, backgroundTiled,			value)
PSTADE_INSTANCE(const lime::ustring, focusObjectID,				value)
PSTADE_INSTANCE(const lime::ustring, maxHeight,					value)
PSTADE_INSTANCE(const lime::ustring, maxWidth,					value)
PSTADE_INSTANCE(const lime::ustring, minHeight,					value)
PSTADE_INSTANCE(const lime::ustring, minWidth,					value)
PSTADE_INSTANCE(const lime::ustring, resizable,					value)
PSTADE_INSTANCE(const lime::ustring, resizeBackgroundImage,		value)
PSTADE_INSTANCE(const lime::ustring, scriptFile,				value)
PSTADE_INSTANCE(const lime::ustring, timerInterval,				value)
PSTADE_INSTANCE(const lime::ustring, title,						value)
PSTADE_INSTANCE(const lime::ustring, titleBar,					value)
PSTADE_INSTANCE(const lime::ustring, transparencyColor,			value)


} } // namespace pstade::hamburger


#endif
