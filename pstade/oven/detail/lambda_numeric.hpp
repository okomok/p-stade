#ifndef PSTADE_OVEN_DETAIL_LAMBDA_NUMERIC_HPP
#define PSTADE_OVEN_DETAIL_LAMBDA_NUMERIC_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// <boost/lambda/core.hpp> is too big.
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/remove_const.hpp>
#if !defined(BOOST_LAMBDA_CORE_HPP)
    #define BOOST_LAMBDA_CORE_HPP
    #include <boost/lambda/numeric.hpp>
    #undef  BOOST_LAMBDA_CORE_HPP
#else
    #include <boost/lambda/numeric.hpp>
#endif


#endif
