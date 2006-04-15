#ifndef PSTADE_INSTANCE_HPP
#define PSTADE_INSTANCE_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: <boost/sequence/detail/instance.hpp>
//
// Copyright David Abrahams 2005. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// The ODR violation buster.


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/utility/value_init.hpp> // value_initialized


// Workaround:
// 'static' is still needed for weird 'stdafx.h'.
//
#define PSTADE_INSTANCE(Type, Name) \
	PSTADE_INSTANCE_define_instance_fun(Type, Name, PSTADE_INSTANCE_define_x_0(Type)) \
	namespace { \
		static Type& Name = PSTADE_INSTANCE_call_instance_fun(Name); \
	} \
/**/


#define PSTADE_INSTANCE_ARGS(Type, Name, ArgSeq) \
	PSTADE_INSTANCE_define_instance_fun(Type, Name, PSTADE_INSTANCE_define_x_a(Type, ArgSeq)) \
	namespace { \
		static Type& Name = PSTADE_INSTANCE_call_instance_fun(Name); \
	} \
/**/


	#define PSTADE_INSTANCE_define_instance_fun(Type, Name, DefineX) \
		inline \
		Type& BOOST_PP_CAT(pstade_instance_of_, Name)() \
		{ \
			static DefineX \
			return x; \
		} \
	/**/


	#define PSTADE_INSTANCE_call_instance_fun(Name) \
		BOOST_PP_CAT(pstade_instance_of_, Name)() \
	/**/


	#define PSTADE_INSTANCE_define_x_0(Type) \
		boost::value_initialized< Type > x; \
	/**/


	#define PSTADE_INSTANCE_define_x_a(Type, ArgSeq) \
		Type x(BOOST_PP_SEQ_ENUM(ArgSeq)); \
	/**/


#endif
