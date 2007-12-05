#ifndef PSTADE_EGG_RETURN_HPP
#define PSTADE_EGG_RETURN_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/lambda.hpp>
#include <pstade/adl_barrier.hpp>
#include "./by_perfect.hpp"
#include "./by_value.hpp"
#include "./detail/baby_return_result.hpp"
#include "./generator.hpp"
#include "./specified.hpp"
#include "./use_brace_level1.hpp"


namespace pstade { namespace egg {


    template<class Base, class Lambda, class Strategy = by_perfect>
    struct result_of_return_
    {
        typedef
            function<detail::baby_return_result<Base, Lambda>, Strategy>
        type;
    };


    #define PSTADE_EGG_RETURN_L { {
    #define PSTADE_EGG_RETURN_R } }


    template<class Lambda>
    struct X_return_ :
        generator<
            typename result_of_return_<
                deduce<boost::mpl::_1, as_value>,
                typename boost::mpl::lambda<Lambda>::type
            >::type,
            boost::use_default,
            use_brace_level1,
            by_value
        >::type
    { };


    PSTADE_EGG_SPECIFIED1(return_, X_return_, (class))


} } // namespace pstade::egg


#endif