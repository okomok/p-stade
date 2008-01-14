#ifndef BOOST_EGG_PERFECT_HPP
#define BOOST_EGG_PERFECT_HPP
#include "./detail/prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/pstade/pod_constant.hpp>
#include "./return.hpp"


namespace pstade { namespace egg {


    template<class Base>
    struct result_of_perfect :
        result_of_return<Base>
    { };


    #define BOOST_EGG_PERFECT_L BOOST_EGG_RETURN_L
    #define BOOST_EGG_PERFECT_R BOOST_EGG_RETURN_R
    #define BOOST_EGG_PERFECT(F) BOOST_EGG_PERFECT_L F BOOST_EGG_PERFECT_R


    typedef X_return<>::function_type T_perfect;
    PSTADE_POD_CONSTANT((T_perfect), perfect) = BOOST_EGG_GENERATOR();


} } // namespace pstade::egg


#endif
