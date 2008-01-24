#ifndef PSTADE_EGG_UNFUSE_HPP
#define PSTADE_EGG_UNFUSE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./by_perfect.hpp"
#include "./by_value.hpp"
#include "./detail/little_unfuse_result.hpp"
#include "./generator.hpp"
#include "./use_brace2.hpp"


namespace pstade { namespace egg {


    template<
        class Base,
        class Pack          = boost::use_default,
        class NullaryResult = boost::use_default,
        class Strategy      = by_perfect
    >
    struct result_of_unfuse
    {
        typedef
            function<detail::little_unfuse_result<Base, Pack, NullaryResult>, Strategy>
        type;
    };

    #define PSTADE_EGG_UNFUSE_L { {
    #define PSTADE_EGG_UNFUSE_M ,
#if defined(PSTADE_EGG_HAS_FUSIONS)
    #define PSTADE_EGG_UNFUSE_DEFAULT_PACK PSTADE_EGG_FUSION_PACK_INIT
#else
    #define PSTADE_EGG_UNFUSE_DEFAULT_PACK PSTADE_EGG_TUPLE_PACK_INIT
#endif
    #define PSTADE_EGG_UNFUSE_R } }
    #define PSTADE_EGG_UNFUSE(F) PSTADE_EGG_UNFUSE_L F PSTADE_EGG_UNFUSE_M PSTADE_EGG_UNFUSE_DEFAULT_PACK PSTADE_EGG_UNFUSE_R


    template<class NullaryResult = boost::use_default, class Strategy = boost::use_default>
    struct X_unfuse :
        generator<
            typename result_of_unfuse<
                deduce<mpl_1, as_value>, deduce<mpl_2, as_value, boost::use_default>,
                NullaryResult, Strategy
            >::type,
            by_value,
            use_brace2
        >::type
    { };

    typedef X_unfuse<>::function_type T_unfuse;
    PSTADE_POD_CONSTANT((T_unfuse), unfuse) = PSTADE_EGG_GENERATOR();


} } // namespace pstade::egg


#endif
