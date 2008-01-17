#ifndef PSTADE_EGG_LAZY_HPP
#define PSTADE_EGG_LAZY_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./by_cref.hpp"
#include "./by_value.hpp"
#include "./detail/little_lazy_result.hpp"
#include "./generator.hpp"
#include "./use_brace2.hpp"


namespace pstade { namespace egg {


    template<class Base, class Bind = boost::use_default>
    struct result_of_lazy
    {
        typedef
            function<detail::little_lazy_result<Base, Bind>, by_cref>
        type;
    };


    #define PSTADE_EGG_LAZY_L { {
    #define PSTADE_EGG_LAZY_M ,
    #define PSTADE_EGG_LAZY_DEFAULT_BIND PSTADE_EGG_BLL_BIND_INIT
    #define PSTADE_EGG_LAZY_R } }
    #define PSTADE_EGG_LAZY(F) PSTADE_EGG_LAZY_L F PSTADE_EGG_LAZY_M PSTADE_EGG_LAZY_DEFAULT_BIND PSTADE_EGG_LAZY_R


    typedef
        generator<
            result_of_lazy< deduce<mpl_1, as_value>, deduce<mpl_2, as_value, boost::use_default> >::type,
            by_value,
            use_brace2
        >::type
    T_lazy;

    PSTADE_POD_CONSTANT((T_lazy), lazy) = PSTADE_EGG_GENERATOR();


} } // namespace pstade::egg


#endif
