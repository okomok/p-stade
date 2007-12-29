#ifndef PSTADE_EGG_UNCURRY_HPP
#define PSTADE_EGG_UNCURRY_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./detail/baby_uncurry_result.hpp"
#include "./by_perfect.hpp"
#include "./by_value.hpp"
#include "./generator.hpp"
#include "./use_brace2.hpp"


namespace pstade { namespace egg {


    template<class Base, class Strategy = by_perfect>
    struct result_of_uncurry
    {
        typedef
            function<detail::baby_uncurry_result<Base>, Strategy>
        type;
    };


    #define PSTADE_EGG_UNCURRY_L { {
    #define PSTADE_EGG_UNCURRY_R } }
    #define PSTADE_EGG_UNCURRY(F) PSTADE_EGG_UNCURRY_L F PSTADE_EGG_UNCURRY_R


    typedef
        generator<
            result_of_uncurry< deduce<boost::mpl::_1, as_value> >::type,
            boost::use_default,
            use_brace2,
            by_value
        >::type
    T_uncurry;


    PSTADE_POD_CONSTANT((T_uncurry), uncurry) = {{}};


} } // namespace pstade::egg


#endif
