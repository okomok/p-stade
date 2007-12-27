#ifndef PSTADE_EGG_NOT_HPP
#define PSTADE_EGG_NOT_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./by_perfect.hpp"
#include "./by_value.hpp"
#include "./detail/baby_not_result.hpp"
#include "./generator.hpp"
#include "./use_brace2.hpp"


namespace pstade { namespace egg {


    template<class Base, class Strategy = by_perfect>
    struct result_of_not_
    {
        typedef
            function<detail::baby_not_result<Base>, Strategy>
        type;
    };


    #define PSTADE_EGG_NOT_L { {
    #define PSTADE_EGG_NOT_R } }


    typedef
        generator<
            result_of_not_< deduce<boost::mpl::_1, as_value> >::type,
            boost::use_default,
            use_brace2,
            by_value
        >::type
    T_not_;


    PSTADE_POD_CONSTANT((T_not_), not_) = PSTADE_EGG_GENERATOR;


} } // namespace pstade::egg


#endif
