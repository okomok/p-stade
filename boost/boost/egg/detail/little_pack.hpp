#ifndef BOOST_EGG_DETAIL_LITTLE_PACK_HPP
#define BOOST_EGG_DETAIL_LITTLE_PACK_HPP
#include "./prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/egg/pstade/pod_constant.hpp>
#include <boost/egg/pstade/preprocessor.hpp>
#include "../apply_decl.hpp"
#include "../by_ref.hpp"
#include "../config.hpp"

   
#define BOOST_EGG_LITTLE_PACK() <boost/egg/detail/little_pack_include.hpp>


#endif
