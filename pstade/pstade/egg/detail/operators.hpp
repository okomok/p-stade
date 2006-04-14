#ifndef PSTADE_EGG_DETAIL_OPERATORS_HPP
#define PSTADE_EGG_DETAIL_OPERATORS_HPP


// PStade.Egg
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/add_const.hpp>
#include "../baby_call.hpp"
#include "../baby_result_type.hpp"


namespace pstade { namespace egg { namespace detail {


template< class BabyFunction >
struct operators
{

	// 0ary
	//
	typename baby_result0<BabyFunction
	>::type
	operator()(
	) const
	{
		return egg::baby_call<BabyFunction>();
	}


	// 1ary
	//
	template< class A0 >
	typename baby_result1<BabyFunction,
		A0
	>::type
	operator()(
		A0& a0
	) const
	{
		return egg::baby_call<BabyFunction>(a0);
	}

	template< class A0 >
	typename baby_result1<BabyFunction,
		typename boost::add_const<A0>::type
	>::type
	operator()(
		const A0& a0
	) const
	{
		return egg::baby_call<BabyFunction>(a0);
	}


	// 2ary
	//
	template< class A0, class A1 >
	typename baby_result2<BabyFunction,
		A0,
		A1
	>::type
	operator()(
		A0& a0,
		A1& a1
	) const
	{
		return egg::baby_call<BabyFunction>(a0, a1);
	}

	template< class A0, class A1 >
	typename baby_result2<BabyFunction,
		A0,
		typename boost::add_const<A1>::type
	>::type
	operator()(
		A0& a0,
		const A1& a1
	) const
	{
		return egg::baby_call<BabyFunction>(a0, a1);
	}

	template< class A0, class A1 >
	typename baby_result2<BabyFunction,
		typename boost::add_const<A0>::type,
		A1
	>::type
	operator()(
		const A0& a0,
		A1& a1
	) const
	{
		return egg::baby_call<BabyFunction>(a0, a1);
	}

	template< class A0, class A1 >
	typename baby_result2<BabyFunction,
		typename boost::add_const<A0>::type,
		typename boost::add_const<A1>::type
	>::type
	operator()(
		const A0& a0,
		const A1& a1
	) const
	{
		return egg::baby_call<BabyFunction>(a0, a1);
	}


	// 3ary
	//
	template< class A0, class A1, class A2 >
	typename baby_result3<BabyFunction,
		A0,
		A1,
		A2
	>::type
	operator()(
		A0& a0,
		A1& a1,
		A2& a2
	) const
	{
		return egg::baby_call<BabyFunction>(a0, a1, a2);
	}

}; // struct operators


} } } // namespace pstade::egg::detail


#endif
