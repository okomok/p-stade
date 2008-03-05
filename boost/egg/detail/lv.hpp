#ifndef BOOST_EGG_DETAIL_LV_HPP
#define BOOST_EGG_DETAIL_LV_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/lambda/core.hpp> // protect
#include <boost/egg/by_value.hpp>
#include <boost/egg/compose.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/identity.hpp>
#include <boost/egg/overloaded.hpp>
#include <boost/egg/bll/result_of.hpp> // inclusion guaranteed


namespace boost { namespace egg {


    namespace lv_detail {


        struct little
        {
            BOOST_EGG_OVERLOADED_PREAMBLE()

            template<class Me, class T>
            struct apply
            {
                typedef T type;
            };

            template<class Me, class Arg>
            struct apply< Me, lambda::lambda_functor<Arg> >
            {
                typedef
                    lambda::lambda_functor<
                        lambda::lambda_functor_base<
                            lambda::protect_action,
                            tuples::tuple< lambda::lambda_functor<Arg> >
                        >
                    >
                type;
            };

            template<class Re, class T>
            Re call(BOOST_EGG_OVERLOADED(Re) T t) const
            {
                return t;
            }

            template<class Re, class Arg>
            Re call(BOOST_EGG_OVERLOADED(Re) lambda::lambda_functor<Arg> lam) const
            {
                return
                    lambda::lambda_functor_base<
                        lambda::protect_action,
                        tuples::tuple< lambda::lambda_functor<Arg> >
                    >(tuples::tuple< lambda::lambda_functor<Arg> >(lam));
            }
        };


    } // namespace lv_detail


    typedef X_identity<by_value>::base_class T_lv0;
    BOOST_EGG_CONST((T_lv0), lv0) = {{}};

    #define BOOST_EGG_LV1_INIT {{}}
    typedef function<lv_detail::little, by_value> T_lv1;
    BOOST_EGG_CONST((T_lv1), lv1) = BOOST_EGG_LV1_INIT;

    #define BOOST_EGG_LV2_INIT BOOST_EGG_COMPOSE_L BOOST_EGG_LV1_INIT, BOOST_EGG_LV1_INIT BOOST_EGG_COMPOSE_R
    typedef result_of_compose<T_lv1, T_lv1, use_default, by_value>::type T_lv2;
    BOOST_EGG_CONST((T_lv2), lv2) = BOOST_EGG_LV2_INIT;

    #define BOOST_EGG_LV3_INIT BOOST_EGG_COMPOSE_L BOOST_EGG_LV1_INIT, BOOST_EGG_LV2_INIT BOOST_EGG_COMPOSE_R
    typedef result_of_compose<T_lv1, T_lv2, use_default, by_value>::type T_lv3;
    BOOST_EGG_CONST((T_lv3), lv3) = BOOST_EGG_LV3_INIT;

    #define BOOST_EGG_LV4_INIT BOOST_EGG_COMPOSE_L BOOST_EGG_LV1_INIT, BOOST_EGG_LV3_INIT BOOST_EGG_COMPOSE_R
    typedef result_of_compose<T_lv1, T_lv3, use_default, by_value>::type T_lv4;
    BOOST_EGG_CONST((T_lv4), lv4) = BOOST_EGG_LV4_INIT;


} } // namespace boost::egg


#endif
