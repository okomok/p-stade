#ifndef PSTADE_EGG_LAZY_HPP
#define PSTADE_EGG_LAZY_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/result_of_lambda.hpp> // inclusion guaranteed.
#include "./by_cref.hpp"
#include "./by_value.hpp"
#include "./detail/baby_lazy_result.hpp"
#include "./generator.hpp"
#include "./specified.hpp"
#include "./use_brace2.hpp"


namespace pstade { namespace egg {


    template<class Base>
    struct result_of_lazy
    {
        typedef
            function<detail::baby_lazy_result<Base>, by_cref>
        type;
    };


    #define PSTADE_EGG_LAZY_L { {
    #define PSTADE_EGG_LAZY_R } }
    #define PSTADE_EGG_LAZY(F) PSTADE_EGG_LAZY_L F PSTADE_EGG_LAZY_R

    typedef
        generator<
            result_of_lazy< deduce<boost::mpl::_1, as_value> >::type,
            boost::use_default,
            use_brace2,
            by_value
        >::type
    T_lazy;


    PSTADE_POD_CONSTANT((T_lazy), lazy) = PSTADE_EGG_GENERATOR;



} } // namespace pstade::egg


#endif
