#ifndef PSTADE_EGG_RETBY_HPP
#define PSTADE_EGG_RETBY_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/lambda.hpp> // inclusion guaranteed
#include "./by_perfect.hpp"
#include "./by_value.hpp"
#include "./detail/baby_retby_result.hpp"
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
    struct result_of_retby
    {
        typedef
            function<detail::baby_retby_result<Base, ResultType, Tag>, Strategy>
        type;
    };


    #define PSTADE_EGG_RETBY_L { {
    #define PSTADE_EGG_RETBY_R } }


    template<class ResultType = boost::use_default>
    struct X_retby :
        generator<
            typename result_of_retby<
                deduce<boost::mpl::_1, as_value>,
                typename boost::mpl::lambda<ResultType>::type
            >::type,
            boost::use_default,
            use_brace_level1,
            by_value
        >::type
    { };


    PSTADE_EGG_SPECIFIED1(retby, X_retby, (class))


} } // namespace pstade::egg


#endif
