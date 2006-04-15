#ifndef PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_HPP
#define PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/foreach.hpp> // tag
#include <boost/mpl/bool.hpp> // true_
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/detail/is_unary.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/tuple/eat.hpp>


#define PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY(Name) \
	inline \
	boost::mpl::true_ \
	*boost_foreach_is_lightweight_proxy(Name *&, boost::foreach::tag) \
	{ return 0; } \
/**/


#define PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(Name, ParamSeqOrCount) \
	PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE_impl( \
		Name, \
		PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE_to_param_seq(ParamSeqOrCount) \
	) \
/**/

	#define PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE_to_param_seq(ParamSeqOrCount) \
		BOOST_PP_IIF(BOOST_PP_IS_UNARY(ParamSeqOrCount), \
			ParamSeqOrCount BOOST_PP_TUPLE_EAT(3), \
			BOOST_PP_REPEAT \
		)(ParamSeqOrCount, PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE_to_param_seq_op, ~) \
	/**/

		#define PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE_to_param_seq_op(z, n, _) \
			(class) \
		/**/


#define PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE_impl(Name, ParamSeq) \
	template< PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE_params(ParamSeq) > inline \
	boost::mpl::true_ \
	*boost_foreach_is_lightweight_proxy(Name< BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(ParamSeq), T) > *&, boost::foreach::tag) \
	{ return 0; } \
/**/


#define PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE_params(ParamSeq) \
	BOOST_PP_SEQ_FOR_EACH_I(PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE_params_op, ~, ParamSeq) \
/**/

	#define PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE_params_op(r, data, i, elem) \
		BOOST_PP_COMMA_IF(i) elem BOOST_PP_CAT(T, i) \
	/**/


#endif
