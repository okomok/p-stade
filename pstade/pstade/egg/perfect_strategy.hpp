#ifndef PSTADE_EGG_PERFECT_STRATEGY_HPP
#define PSTADE_EGG_PERFECT_STRATEGY_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
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
#include <pstade/deduced_const.hpp>
#include <pstade/preprocessor.hpp>
#include "./call_little.hpp"
#include "./detail/nullary_result.hpp"
#include "./function_fwd.hpp"
#include "./sig_template.hpp"
#include "./unref_by.hpp"


#define PSTADE_EGG_PERFECT_STRATEGY() <pstade/egg/detail/perfect_strategy_include.hpp>


#endif
