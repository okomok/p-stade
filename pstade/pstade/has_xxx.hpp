#ifndef PSTADE_HAS_XXX_HPP
#define PSTADE_HAS_XXX_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: <boost/spirit/phoenix/stl/container/detail/container.hpp>
//
/*=============================================================================
    Copyright (c) 2004 Angus Leeming
    Copyright (c) 2004 Joel de Guzman

    Use, modification and distribution is subject to the Boost Software
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/


// Why not: BOOST_MPL_HAS_XXX_TRAIT_DEF
//
// http://lists.boost.org/Archives/boost/2005/10/95809.php


#include <boost/mpl/bool.hpp>
#include <boost/preprocessor/cat.hpp>


#define PSTADE_HAS_XXX(Tag) \
	struct BOOST_PP_CAT(pstade_has_xxx_one_, Tag) { char a[1]; }; \
	struct BOOST_PP_CAT(pstade_has_xxx_two_, Tag) { char a[2]; }; \
	\
	template< class T > \
	BOOST_PP_CAT(pstade_has_xxx_one_, Tag) BOOST_PP_CAT(pstade_has_xxx_aux_, Tag)(typename T::Tag(*)()); \
	\
	template< class T > \
	BOOST_PP_CAT(pstade_has_xxx_two_, Tag) BOOST_PP_CAT(pstade_has_xxx_aux_, Tag)(...); \
	\
	template< class T > \
	struct BOOST_PP_CAT(has_, Tag) : \
		boost::mpl::bool_< \
			sizeof(BOOST_PP_CAT(pstade_has_xxx_aux_, Tag)<T>(0)) == \
				sizeof(BOOST_PP_CAT(pstade_has_xxx_one_, Tag)) \
		> \
	{ }; \
/**/


#endif
