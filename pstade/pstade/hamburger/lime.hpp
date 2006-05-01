#ifndef PSTADE_HAMBURGER_LIME_HPP
#define PSTADE_HAMBURGER_LIME_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <memory> // auto_ptr
#include <boost/assert.hpp>
#include <pstade/lime/ustring.hpp>
#include <pstade/oven/equal.hpp>
#include "./button.hpp"
#include "./desktop.hpp"
#include "./element.hpp"
#include "./subview.hpp"
#include "./view.hpp"


namespace pstade { namespace hamburger {


inline // lime customization
element_node *pstade_lime_new_node(element_node& parent, lime::ustring childName)
{
	std::auto_ptr<element_node> pe;

	if (oven::equals(childName, subview_name)) {
		
		pe.reset(new view(parent));
	}
	else if (oven::equals(childName, view_name)) {
		
		pe.reset(new subview(parent));
	}
	else if (oven::equals(childName, button_name)) {
		
		pe.reset(new button(parent));
	}
	else if (oven::equals(childName, desktop_name)) {
		
		pe.reset(new desktop());
	}
	else {
		BOOST_ASSERT(false);
		pe.reset(new element("unknown"));
	}

	return pe.release();
}


} } // namespace pstade::hamburger


#endif
