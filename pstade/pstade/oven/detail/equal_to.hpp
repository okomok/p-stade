#ifndef PSTADE_OVEN_DETAIL_EQUAL_TO_HPP
#define PSTADE_OVEN_DETAIL_EQUAL_TO_HPP


// PStade.Oven
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// equal_to
//
// Copyright Pavol Droba 2002-2003. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace oven { namespace detail {


struct equal_to
{
	template< class A0, class A1 >
	bool operator()(const A0& a0, const A1& a1) const
	{
		return a0 == a1;
	}
};


} } } // namespace pstade::oven::detail


#endif
