#ifndef PSTADE_OVEN_DETAIL_BABY_TO_ADAPTOR_HPP
#define PSTADE_OVEN_DETAIL_BABY_TO_ADAPTOR_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/unparenthesize.hpp>


#define PSTADE_OVEN_BABY_TO_ADAPTOR(O, F) \
    typedef pstade::egg::function<PSTADE_UNPARENTHESIZE(F)> BOOST_PP_CAT(T_make_, O); \
    PSTADE_POD_CONSTANT((BOOST_PP_CAT(T_make_, O)), BOOST_PP_CAT(make_, O)) = {{}}; \
    PSTADE_POD_CONSTANT((pstade::egg::result_of_pipable<BOOST_PP_CAT(T_make_, O)>::type), O) = PSTADE_EGG_PIPABLE({{}}); \
/**/


#endif
