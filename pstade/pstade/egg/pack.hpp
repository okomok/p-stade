#ifndef PSTADE_EGG_PACK_HPP
#define PSTADE_EGG_PACK_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/tuple/tuple.hpp>
#include <pstade/boost_tuple_config.hpp> // PSTADE_BOOST_TUPLE_MAX_SIZE
#include "./detail/xxx_pack.hpp"


#define  PSTADE_EGG_PACK_TEMPLATE(_) boost::tuples::tuple
#define  PSTADE_EGG_XXX_PACK_PARAMS (pack, PSTADE_EGG_PACK_TEMPLATE, PSTADE_BOOST_TUPLE_MAX_SIZE)
#include PSTADE_EGG_XXX_PACK()


#include "./detail/suffix.hpp"
#endif
