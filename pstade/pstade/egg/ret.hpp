#ifndef PSTADE_EGG_RET_HPP
#define PSTADE_EGG_RET_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/adl_barrier.hpp>
#include "./by_perfect.hpp"
#include "./detail/baby_ret_result.hpp"
#include "./generator.hpp"
#include "./specified.hpp"
#include "./use_brace_level1.hpp"


namespace pstade { namespace egg {


    template<
        class Base,
        class ResultType = boost::use_default,
        class Strategy   = by_perfect,
        class Tag        = boost::use_default
    >
    struct result_of_ret
    {
        typedef
            function<detail::baby_ret_result<Base, ResultType, Tag>, Strategy>
        type;
    };


    #define PSTADE_EGG_RET_L { {
    #define PSTADE_EGG_RET_R } }


    namespace ret_detail {


        template<class ResultType>
        struct pod_ :
            generator<
                typename result_of_ret<deduce<boost::mpl::_1, as_value>, ResultType>::type,
                boost::use_default,
                use_brace_level1
            >
        { };


    } // namespace ret_detail


    template<class ResultType = boost::use_default>
    struct X_ret :
        ret_detail::pod_<ResultType>::type
    {
        typedef typename ret_detail::pod_<ResultType>::type pod_type;
    };


    PSTADE_ADL_BARRIER(ret) { // for 'boost'
        PSTADE_EGG_SPECIFIED1(ret, X_ret, (class))
    }


} } // namespace pstade::egg


#endif
