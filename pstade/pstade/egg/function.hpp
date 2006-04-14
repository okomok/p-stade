#ifndef PSTADE_EGG_FUNCTION_HPP
#define PSTADE_EGG_FUNCTION_HPP


// PStade.Egg
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/seq/cat.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/instance.hpp>
#include "./detail/config.hpp"
#include "./detail/operators.hpp"
#include "./detail/results.hpp"
#include "./baby_result_type.hpp"
#include "./function_fwd.hpp"


namespace pstade { namespace egg {


template< class BabyFunction >
struct function :
	detail::operators<BabyFunction>,
	detail::results<BabyFunction>
{ };


} } // namespace pstade::egg


namespace boost {


	template< class BabyFunction >
	struct result_of<pstade::egg::function<BabyFunction>(void)> : // CWPro8 requires an argument 'void'
		pstade::egg::baby_result0<BabyFunction>
	{ };


#if defined(PSTADE_EGG_DETAIL_NO_NESTED_RESULT_SPECIALIZATION)


	template< class BabyFunction, class A0 >
	struct result_of<pstade::egg::function<BabyFunction>(A0)> :
		pstade::egg::baby_result1<BabyFunction, A0>
	{ };


	template< class BabyFunction, class A0, class A1 >
	struct result_of<pstade::egg::function<BabyFunction>(A0, A1)> :
		pstade::egg::baby_result2<BabyFunction, A0, A1>
	{ };


	template< class BabyFunction, class A0, class A1, class A2 >
	struct result_of<pstade::egg::function<BabyFunction>(A0, A1, A2)> :
		pstade::egg::baby_result3<BabyFunction, A0, A1, A2>
	{ };


#endif


} // namespace boost


#define PSTADE_EGG_FUNCTION(Name, Baby) \
	typedef pstade::egg::function< Baby > BOOST_PP_SEQ_CAT((Name)(_)(function)); \
	PSTADE_INSTANCE(const pstade::egg::function< Baby >, Name); \
/**/


#endif
