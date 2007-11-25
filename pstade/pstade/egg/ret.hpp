#ifndef PSTADE_EGG_RET_HPP
#define PSTADE_EGG_RET_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/lambda.hpp> // inclusion guaranteed
#include <boost/mpl/protect.hpp>
#include <pstade/adl_barrier.hpp>
#include <pstade/use_default.hpp>
#include "./by_perfect.hpp"
#include "./retby.hpp"
#include "./specified.hpp"


namespace pstade { namespace egg {


    namespace ret_detail {


        template<class T>
        struct to_always :
            if_use_default< T, T, boost::mpl::always<T> >
        { };


    } // namespace ret_detail


    template<
        class Base,
        class ResultType = boost::use_default,
        class Strategy   = by_perfect
    >
    struct result_of_ret :
        result_of_retby<
            Base,
            typename ret_detail::to_always<ResultType>::type,
            Strategy
        >
    { };


    #define PSTADE_EGG_RET_L PSTADE_EGG_RETBY_L
    #define PSTADE_EGG_RET_R PSTADE_EGG_RETBY_R


    template<class ResultType = boost::use_default>
    struct X_ret :
        X_retby<typename ret_detail::to_always<ResultType>::type>
    { };


    PSTADE_ADL_BARRIER(ret) { // for 'boost'
        PSTADE_EGG_SPECIFIED1(ret, X_ret, (class))
    }


} } // namespace pstade::egg


#endif
