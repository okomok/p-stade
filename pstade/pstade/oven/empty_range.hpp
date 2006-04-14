#ifndef PSTADE_OVEN_EMPTY_RANGE_HPP
#define PSTADE_OVEN_EMPTY_RANGE_HPP


// PStade.Oven
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/iterator_range.hpp>
#include <pstade/nullptr.hpp>
#include "./is_lightweight_proxy.hpp"


namespace pstade { namespace oven {


template< class T >
struct empty_range :
	boost::iterator_range<T *>
{
private:
	typedef boost::iterator_range<T *> super_t;

public:
	empty_range() :
		super_t(PSTADE_NULLPTR, PSTADE_NULLPTR)
	{ }
};


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::empty_range, 1)


#endif
