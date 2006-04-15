#ifndef PSTADE_EGG_BABY_CALL_HPP
#define PSTADE_EGG_BABY_CALL_HPP


// PStade.Egg
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./baby_result_type.hpp"


namespace pstade { namespace egg {


template< class BabyFunction >
typename egg::baby_result0<BabyFunction>::type
baby_call()
{
	typedef typename egg::baby_result0<BabyFunction
	>::type result_t;

	return BabyFunction().template call<result_t>();
}


template< class BabyFunction, class A0 >
typename egg::baby_result1<BabyFunction,
	A0
>::type
baby_call(A0& a0)
{
	typedef typename egg::baby_result1<BabyFunction,
		A0
	>::type result_t;

	return BabyFunction().template call<result_t>(a0);
}


template< class BabyFunction, class A0, class A1 >
typename egg::baby_result2<BabyFunction,
	A0, A1
>::type
baby_call(A0& a0, A1& a1)
{
	typedef typename egg::baby_result2<BabyFunction,
		A0, A1
	>::type result_t;

	return BabyFunction().template call<result_t>(a0, a1);
}


template< class BabyFunction, class A0, class A1, class A2>
typename egg::baby_result3<BabyFunction,
	A0, A1, A2
>::type
baby_call(A0& a0, A1& a1, A2& a2)
{
	typedef typename egg::baby_result3<BabyFunction,
		A0, A1, A2
	>::type result_t;

	return BabyFunction().template call<result_t>(a0, a1, a2);
}


} } // namespace pstade::egg


#endif
