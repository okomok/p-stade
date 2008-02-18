#ifndef BOOST_EGG_FUSION_PACK_HPP
#define BOOST_EGG_FUSION_PACK_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/fusion/include/vector.hpp>
#include <boost/egg/detail/xxx_pack.hpp>


// vector0 is not template.
#define  BOOST_EGG_FUSION_PACK_TEMPLATE(_) fusion::vector
#define  BOOST_EGG_XXX_PACK_PARAMS (fusion_pack, BOOST_EGG_FUSION_PACK_TEMPLATE, FUSION_MAX_VECTOR_SIZE)
#include BOOST_EGG_XXX_PACK()


#include <boost/egg/detail/suffix.hpp>
#endif
