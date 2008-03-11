#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_DETAIL_NEST_PLACEHOLDER_HPP
#define BOOST_EGG_DETAIL_NEST_PLACEHOLDER_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/egg/bll/protect.hpp>
#include <boost/egg/by_value.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_MAX_NEST_LEVEL
#include <boost/egg/const.hpp>
#include <boost/egg/detail/derived_from.hpp>
#include <boost/egg/detail/if_use_default.hpp>
#include <boost/egg/identity.hpp>
#include <boost/egg/preprocessor/cat3.hpp>
#include <boost/egg/result_of.hpp>


namespace boost { namespace egg {


// level0
    template<class Protect = use_default>
    struct XX_0_ :
        X_identity<by_value>
    { };

    typedef XX_0_<>::base_class TT_0_;
    BOOST_EGG_CONST((TT_0_), _0_) = {{}};


// level1-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_PP_DEC(BOOST_EGG_MAX_NEST_LEVEL), <boost/egg/detail/nest_placeholder.hpp>))
    #include BOOST_PP_ITERATE()


} } // namespace boost::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    namespace BOOST_EGG_PP_CAT3(nest, n, _placeholder_detail) {


        template<class Protect>
        struct little
        {
            typedef BOOST_EGG_PP_CAT3(XX_, BOOST_PP_DEC(n), _)<Protect> SS_N_1;

            template<class Me, class Placeholder>
            struct apply :
                result_of_<Protect(typename result_of_<SS_N_1(Placeholder &)>::type)>
            { };

            template<class Re, class Placeholder>
            Re call(Placeholder p) const
            {
                return Protect()(SS_N_1()(p));
            }
        };


    } // namespace nestN_placholder_detail


    template<class Protect = use_default>
    struct BOOST_EGG_PP_CAT3(XX_, n, _) : details::derived_from <
        function<
            BOOST_EGG_PP_CAT3(nest, n, _placeholder_detail)::little<
                typename details::if_use_default<Protect, T_bll_protect>::type
            >,
            by_value
        > >
    { };

    typedef BOOST_EGG_PP_CAT3(XX_, n, _)<>::base_class BOOST_EGG_PP_CAT3(TT_, n, _);
    BOOST_EGG_CONST((BOOST_EGG_PP_CAT3(TT_, n, _)), BOOST_EGG_PP_CAT3(_, n, _)) = {{}};


#undef  n
#endif
