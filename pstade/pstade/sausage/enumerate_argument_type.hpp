#ifndef PSTADE_SAUSAGE_ENUMERATE_ARGUMENT_TYPE_HPP
#define PSTADE_SAUSAGE_ENUMERATE_ARGUMENT_TYPE_HPP


// PStade.Sausage
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <pstade/apple/is_boost_range.hpp>
#include <pstade/remove_rcv.hpp>
#include "./detail/boost_range.hpp"
#include "./detail/default_way.hpp"
#include "./detail/has_pstade_sausage_enumerable.hpp"
#include "./detail/intrusive_way.hpp"
#include "./detail/tag_dispatch_way.hpp"


namespace pstade { namespace sausage {


template< class Enumerable >
struct enumerate_argument
{
	typedef typename remove_rcv<Enumerable>::type enm_t;

	typedef typename
	boost::mpl::eval_if< detail::has_pstade_sausage_enumerable<enm_t>,
		detail::intrusive_way_argument<enm_t>,
		boost::mpl::eval_if< detail::is_tag_dispatch_way<enm_t>,
			detail::tag_dispatch_way_argument<enm_t>,
			boost::mpl::eval_if< apple::is_boost_range<enm_t>,
				detail::boost_range_argument<enm_t>,
				detail::default_way_argument<enm_t>
			>
		>
	>::type type;
};


} } // namespace pstade::sausage


#endif
