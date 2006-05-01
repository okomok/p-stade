#ifndef PSTADE_HAMBURGER_SUBVIEW_HPP
#define PSTADE_HAMBURGER_SUBVIEW_HPP


// PStade.Hamburger
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/instance.hpp>
#include "./element.hpp"


namespace pstade { namespace hamburger {


PSTADE_INSTANCE(const lime::ustring, subview_name, ("subview"))


namespace subview_detail {


} // namespace subview_detail


struct subview :
	element
{
private:

public:
	// structors
	//
    explicit subview(element_node& parent) :
        element(parent, subview_name)
	{
	}

	// element
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
};


} } // namespace pstade::hamburger


#endif
