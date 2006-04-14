#ifndef PSTADE_DIET_VALID_HPP
#define PSTADE_DIET_VALID_HPP


// PStade.Diet
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/os.hpp"
#include "./dump.hpp"
#include "./is_valid.hpp"


namespace pstade { namespace diet {


template< class Diagnostic > inline
bool valid(const Diagnostic& dg)
{
	if (!diet::is_valid(dg)) {
		detail::os << "<valid result=\"false\">";
		diet::dump(dg, detail::os);
		detail::os << "</valid>";
		return false;
	}

	return true;
}


} } // namespace pstade::diet


#endif
