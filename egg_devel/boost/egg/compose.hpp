#ifndef BOOST_EGG_COMPOSE_HPP
#define BOOST_EGG_COMPOSE_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/by_value.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/construct_variadic1.hpp>
#include <boost/egg/detail/adl_barrier.hpp>
#include <boost/egg/detail/tuple_fuse.hpp>
#include <boost/egg/generator.hpp>
#include <boost/egg/result_of.hpp>
#include <boost/egg/variadic.hpp>


namespace boost { namespace egg {


    // The nullary result type must be explicitly specified.
    // 'result_of_<F(result_of_<G()>::type)>::type' is always instantiated,
    // but it may be ill-formed, if 'result_of_<G()>::type' is 'void', or
    // an invalid type like 'tuples::null_type' which Boost.Lambda returns instead of 'void'.
    // If such an invalid type is always 'void', then 'result_of_<F()>::type' is always well-formed.
    // But, it is not a general solution. "compose2" to call 'f(g1, g2)' would be ill-formed after all.


    namespace compose_detail {


        template<class F, class G>
        struct little_result
        {
            F m_f;
            G m_g;

            template<class Me, class Args>
            struct apply :
                result_of_<
                    F const(
                        typename result_of_<
                            typename result_of_<details::T_tuple_fuse(G const &)>::type(Args &)
                        >::type
                    )
                >
            { };

            template<class Re, class Args>
            Re call(Args &args) const
            {
                return m_f(details::tuple_fuse(m_g)(args));
            }
        };


    } // namespace compose_detail


    template<class F, class G, class NullaryResult = use_default, class Strategy = use_default>
    struct result_of_compose :
        variadic<
            compose_detail::little_result<F, G>,
            Strategy,
            use_default,
            NullaryResult
        >
    { };

    #define BOOST_EGG_COMPOSE_L BOOST_EGG_VARIADIC_L {
    #define BOOST_EGG_COMPOSE_R } BOOST_EGG_VARIADIC_R
    #define BOOST_EGG_COMPOSE(F, T) BOOST_EGG_COMPOSE_L F , T BOOST_EGG_COMPOSE_R


    template<class NullaryResult = use_default, class Strategy = use_default>
    struct X_compose : details::derived_from_eval<
        generator<
            typename result_of_compose<deduce<mpl::_1, as_value>, deduce<mpl::_2, as_value>, NullaryResult, Strategy>::type,
            by_value,
            X_construct_variadic1<>
        > >
    { };

    typedef X_compose<>::base_class T_compose;
BOOST_EGG_ADL_BARRIER(compose) {
    BOOST_EGG_CONST((T_compose), compose) = BOOST_EGG_GENERATOR();
}


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
