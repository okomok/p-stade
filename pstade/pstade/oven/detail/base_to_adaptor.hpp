#ifndef PSTADE_OVEN_DETAIL_BASE_TO_ADAPTOR_HPP
#define PSTADE_OVEN_DETAIL_BASE_TO_ADAPTOR_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <pstade/egg/deferred.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/pod_constant.hpp>


#define PSTADE_OVEN_BASE_TO_ADAPTOR(O, B) \
    namespace BOOST_PP_CAT(adaptor_workarea_of_, O) { \
        using namespace boost::mpl::placeholders; \
        typedef PSTADE_EGG_DEFER(B) op; \
    } \
    typedef BOOST_PP_CAT(adaptor_workarea_of_, O)::op BOOST_PP_CAT(T_make_, O); \
    PSTADE_POD_CONSTANT((BOOST_PP_CAT(T_make_, O)), BOOST_PP_CAT(make_, O)) = PSTADE_EGG_DEFERRED; \
    PSTADE_POD_CONSTANT((pstade::egg::result_of_pipable<BOOST_PP_CAT(T_make_, O)>::type), O) = PSTADE_EGG_PIPABLE_L PSTADE_EGG_DEFERRED PSTADE_EGG_PIPABLE_R; \
/**/


#endif
