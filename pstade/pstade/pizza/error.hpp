#ifndef PSTADE_PIZZA_ERROR_HPP
#define PSTADE_PIZZA_ERROR_HPP


// PStade.Pizza
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <stdexcept> // runtime_error
#include <string>


namespace pstade { namespace pizza {


struct error :
	std::runtime_error
{
	error(const std::string& msg) :
		std::runtime_error(msg)
	{ }
};


} } // namespace pstade::pizza


#endif
