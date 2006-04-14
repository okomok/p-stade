#ifndef PSTADE_OVEN_SUB_RANGE_RESULT_TYPE_HPP
#define PSTADE_OVEN_SUB_RANGE_RESULT_TYPE_HPP


// PStade.Oven
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Why:
//
// 'boost::sub_range' has no Assignable
// because of a VC++ broken behavior.


#include <boost/range/const_iterator.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>


namespace pstade { namespace oven {


template< class Range >
struct sub_range_result
{
	// 'const' works around "Forwarding Problem".
	typedef const boost::iterator_range<
		typename boost::range_result_iterator<Range>::type
	> type;
};


// In the case of adding explicitly add 'const' to array
// (something like 'sub_range_result<const array>'),
// VC7.1 is confused when ordering. I don't know why, so I define...
// (you can use also boost::add_const for this workaround.)
//
template< class Range >
struct sub_range_result_const
{
	typedef const boost::iterator_range<
		typename boost::range_const_iterator<Range>::type
	> type;
};


} } // namespace pstade::oven


#endif
