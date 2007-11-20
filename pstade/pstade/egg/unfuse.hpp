#ifndef PSTADE_EGG_UNFUSE_HPP
#define PSTADE_EGG_UNFUSE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy tuple_at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>
#include "./by_perfect.hpp"
#include "./by_value.hpp"
#include "./detail/baby_unfuse_result.hpp"
#include "./generator.hpp"
#include "./use_brace_level1.hpp"


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
            function<detail::baby_unfuse_result<Base, Pack, NullaryResult>, Strategy>
        type;
    };


    #define PSTADE_EGG_UNFUSE_L { {
    #define PSTADE_EGG_UNFUSE_M ,
    #define PSTADE_EGG_UNFUSE_DEFAULT_PACK PSTADE_EGG_TUPLE_PACK_INIT
    #define PSTADE_EGG_UNFUSE_R } }


    template<class NullaryResult = boost::use_default>
    struct X_unfuse :
        generator<
            typename result_of_unfuse<
                deduce<boost::mpl::_1, as_value>,
                deduce<boost::mpl::_2, as_value, boost::use_default>,
                NullaryResult
            >::type,
            boost::use_default,
            use_brace_level1,
            by_value
        >::type
    { };


    typedef X_unfuse<>::function_type T_unfuse;
    PSTADE_POD_CONSTANT((T_unfuse), unfuse) = PSTADE_EGG_GENERATOR;


} } // namespace pstade::egg


#endif
