#ifndef BOOST_EGG_PACK_HPP
#define BOOST_EGG_PACK_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/tuple/tuple.hpp>
#include <boost/egg/detail/boost_tuple_fwd.hpp> // BOOST_EGG_BOOST_TUPLE_MAX_SIZE
#include <boost/egg/detail/xxx_pack.hpp>


#define  BOOST_EGG_PACK_TEMPLATE(_) tuples::tuple
#define  BOOST_EGG_XXX_PACK_PARAMS (pack, BOOST_EGG_PACK_TEMPLATE, BOOST_EGG_BOOST_TUPLE_MAX_SIZE)
#include BOOST_EGG_XXX_PACK()


#include <boost/egg/detail/suffix.hpp>
#endif
