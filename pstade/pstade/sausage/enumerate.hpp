#ifndef PSTADE_SAUSAGE_ENUMERATE_HPP
#define PSTADE_SAUSAGE_ENUMERATE_HPP


// PStade.Sausage
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Concepts:
//
// Enumerable: properly customized using below
// EnumFunctor: 'if (fun(x))' is valid


#include <boost/mpl/eval_if.hpp>
#include <pstade/apple/is_boost_range.hpp>
#include <pstade/remove_rcv.hpp>
#include "./detail/boost_range.hpp"
#include "./detail/default_way.hpp"
#include "./detail/has_pstade_sausage_enumerable.hpp"
#include "./detail/intrusive_way.hpp"
#include "./detail/tag_dispatch_way.hpp"


namespace pstade { namespace sausage {


namespace enumerate_detail {


	template< class Enumerable, class EnumFtor > inline
	EnumFtor aux(Enumerable& x, EnumFtor fun)
	{
		using namespace detail;

		typedef typename remove_rcv<Enumerable>::type enm_t;

		typedef typename
		boost::mpl::eval_if< has_pstade_sausage_enumerable<enm_t>,
			intrusive_way,
			boost::mpl::eval_if< is_tag_dispatch_way<enm_t>,
				tag_dispatch_way,
				boost::mpl::eval_if< apple::is_boost_range<enm_t>,
					boost_range,
					default_way
				>
			>
		>::type impl_t;

		return impl_t::call(x, fun);
	};


} // namespace enumerate_detail


template< class Enumerable, class EnumFtor > inline
EnumFtor enumerate(Enumerable& e, EnumFtor fun)
{
	return enumerate_detail::aux(e, fun);
};


template< class Enumerable, class EnumFtor > inline
EnumFtor enumerate(const Enumerable& e, EnumFtor fun)
{
	return enumerate_detail::aux(e, fun);
};


} } // namespace pstade::sausage


#endif
