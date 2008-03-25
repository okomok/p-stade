#ifndef BOOST_EGG_UNFUSE_HPP
#define BOOST_EGG_UNFUSE_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/placeholders.hpp> // inclusion guaranteed
#include <boost/egg/by_perfect.hpp>
#include <boost/egg/by_ref.hpp>
#include <boost/egg/by_value.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/construct_braced2.hpp>
#include <boost/egg/detail/before_mpl_apply.hpp>
#include <boost/egg/detail/derived_from.hpp>
#include <boost/egg/detail/if_use_default.hpp>
#include <boost/egg/detail/little_unfuse_result.hpp>
#include <boost/egg/generator.hpp>
#include <boost/egg/pack.hpp>


namespace boost { namespace egg {


    template<
        class Base,
        class NullaryResult = use_default,
        class PackExpr      = use_default,
        class Strategy      = by_perfect
    >
    struct result_of_unfuse
    {
        // To keep movable object movable, by_ref is used for now.
        typedef typename
            details::eval_if_use_default< PackExpr,
                mpl::identity< X_pack<by_ref> >,
                mpl::apply1<BOOST_EGG_BEFORE_MPL_APPLY_TPL(PackExpr), by_ref>
            >::type
        pack_t;

        typedef
            function<details::little_unfuse_result<Base, NullaryResult, pack_t>, Strategy>
        type;
    };

    #define BOOST_EGG_UNFUSE_L { {
    #define BOOST_EGG_UNFUSE_R } }
    #define BOOST_EGG_UNFUSE(F) BOOST_EGG_UNFUSE_L F BOOST_EGG_UNFUSE_R


    template<
        class NullaryResult = use_default,
        class PackExpr      = use_default,
        class Strategy      = by_perfect
    >
    struct X_unfuse : details::derived_from_eval<
        generator<
            typename result_of_unfuse<deduce<mpl::_1, as_value>, NullaryResult, PackExpr, Strategy>::type,
            by_value,
            X_construct_braced2<>
        > >
    { };

    typedef X_unfuse<>::base_class T_unfuse;
    BOOST_EGG_CONST((T_unfuse), unfuse) = BOOST_EGG_GENERATOR();


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
