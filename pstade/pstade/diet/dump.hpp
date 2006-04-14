#ifndef PSTADE_DIET_DUMP_HPP
#define PSTADE_DIET_DUMP_HPP


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


template< class Diagnostic, class OStream > inline
void dump(const Diagnostic& dg, OStream& os)
{
	typedef customization::point<
		typename customization::tag<Diagnostic>::type
	> point_t;

	point_t().dump(dg, os);
}


} } // namespace pstade::diet


// predefined ones
//
template< class T, std::size_t sz, class OStream >
void pstade_diet_dump(const T (&arr)[sz], OStream& os, pstade::overload)
{
	os << "<array>";

	BOOST_FOREACH (const T& x, arr) {
		pstade::diet::dump(x, os);
	}

	os << "</array>";
}


#endif
