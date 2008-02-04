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
#include <pstade/use_default.hpp>
#include "./by_perfect.hpp"
#include "./by_ref.hpp"
#include "./by_value.hpp"
#include "./construct_braced2.hpp"
#include "./detail/before_mpl_apply.hpp"
#include "./detail/default_pack.hpp"
#include "./detail/little_unfuse_result.hpp"
#include "./detail/mpl_placeholders.hpp" // inclusion guaranteed
#include "./generator.hpp"


namespace pstade { namespace egg {


    template<
        class Base,
        class NullaryResult = boost::use_default,
        class PackExpr      = boost::use_default,
        class Strategy      = by_perfect
    >
    struct result_of_unfuse
    {
        typedef typename
            eval_if_use_default< PackExpr,
                boost::mpl::identity< PSTADE_EGG_DEFAULT_PACK<by_ref> >,
                boost::mpl::apply1<PSTADE_EGG_BEFORE_MPL_APPLY_TPL(PackExpr), by_ref>
            >::type
        pack_t;

        typedef
            function<detail::little_unfuse_result<Base, NullaryResult, pack_t>, Strategy>
        type;
    };

    #define PSTADE_EGG_UNFUSE_L { {
    #define PSTADE_EGG_UNFUSE_R } }
    #define PSTADE_EGG_UNFUSE(F) PSTADE_EGG_UNFUSE_L F PSTADE_EGG_UNFUSE_R


    template<
        class NullaryResult = boost::use_default,
        class PackExpr      = boost::use_default,
        class Strategy      = by_perfect
    >
    struct X_unfuse :
        generator<
            typename result_of_unfuse<deduce<mpl_1, as_value>, NullaryResult, PackExpr, Strategy>::type,
            by_value,
            X_construct_braced2<>
        >::type
    { };

    typedef X_unfuse<>::function_type T_unfuse;
    PSTADE_POD_CONSTANT((T_unfuse), unfuse) = PSTADE_EGG_GENERATOR();


} } // namespace pstade::egg


#endif
