#ifndef PSTADE_DIET_IS_VALID_HPP
#define PSTADE_DIET_IS_VALID_HPP


// PStade.Diet
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t
#include <boost/foreach.hpp>
#include "./detail/default_customization.hpp"
#include "./detail/intrusive_customization.hpp"


namespace pstade { namespace diet {


template< class Diagnostic > inline
bool is_valid(Diagnostic& dg)
{
	typedef customization::point<
		typename customization::tag<Diagnostic>::type
	> point_t;

	return point_t().is_valid(dg);
}


} } // namespace pstade::diet


// predefined ones
//
template< class T, std::size_t sz >
bool pstade_diet_is_valid(const T (&arr)[sz], pstade::overload)
{
	BOOST_FOREACH (const T& x, arr) {
		if (!pstade::diet::is_valid(x))
			return false;
	}

	return true;
}


#endif
