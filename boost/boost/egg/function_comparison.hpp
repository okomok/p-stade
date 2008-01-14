#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_FUNCTION_COMPARISON_HPP
#define BOOST_EGG_FUNCTION_COMPARISON_HPP
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
#include <boost/preprocessor/iteration/iterate.hpp>
#include "./function_fwd.hpp"


namespace pstade { namespace egg {


#define PSTADE_ops (6, (==, !=, <, >, <=, >=))
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_PP_DEC(BOOST_PP_ARRAY_SIZE(PSTADE_ops)), <boost/egg/function_comparison.hpp>))
    #include BOOST_PP_ITERATE()
#undef  PSTADE_ops


} } // namespace pstade::egg


#endif
#else
#define op BOOST_PP_ARRAY_ELEM(BOOST_PP_ITERATION(), PSTADE_ops)


    template<class L1, class S1, class L2, class S2> inline
    bool operator op (function<L1, S1> const& left, function<L2, S2> const& right)
    {
        return left.little() op right.little();
    }


#undef op
#endif
