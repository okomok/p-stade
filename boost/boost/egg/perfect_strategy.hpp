#ifndef BOOST_EGG_PERFECT_STRATEGY_HPP
#define BOOST_EGG_PERFECT_STRATEGY_HPP
#include "./detail/prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/array/elem.hpp>
#include <boost/preprocessor/array/size.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/for_each_product.hpp>
#include <boost/preprocessor/seq/to_array.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/egg/pstade/deduced_const.hpp>
#include <boost/egg/pstade/preprocessor.hpp>
#include "./detail/apply_little_n.hpp"
#include "./detail/call_little_impl.hpp"
#include "./detail/function_preamble.hpp"
#include "./function_fwd.hpp"


#define BOOST_EGG_PERFECT_STRATEGY() <boost/egg/detail/perfect_strategy_include.hpp>


#endif
