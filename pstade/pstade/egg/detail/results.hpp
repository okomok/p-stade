#ifndef PSTADE_EGG_DETAIL_RESULTS_HPP
#define PSTADE_EGG_DETAIL_RESULTS_HPP


// PStade.Egg
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./config.hpp"
#include "../baby_result_type.hpp"


namespace pstade { namespace egg { namespace detail {


template< class BabyFunction >
struct results
{
#if !defined(PSTADE_EGG_DETAIL_NO_NESTED_RESULT_SPECIALIZATION)


	template< class F_Args >
	struct result;


	template< class F_, class A0 >
	struct result<F_(A0)> :
		baby_result1<BabyFunction, A0>
	{ };


	template< class F_, class A0, class A1 >
	struct result<F_(A0, A1)> :
		baby_result2<BabyFunction, A0, A1>
	{ };


	template< class F_, class A0, class A1, class A2 >
	struct result<F_(A0, A1, A2)> :
		baby_result3<BabyFunction, A0, A1, A2>
	{ };


#endif
};


} } } // namespace pstade::egg::detail


#endif
