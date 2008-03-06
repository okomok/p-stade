#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_NEST_HPP
#define BOOST_EGG_NEST_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/egg/bll/bind.hpp>
#include <boost/egg/bll/protect.hpp>
#include <boost/egg/by_value.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_MAX_NEST_LEVEL
#include <boost/egg/const.hpp>
#include <boost/egg/detail/derived_from.hpp>
#include <boost/egg/detail/enable_if.hpp>
#include <boost/egg/detail/if_use_default.hpp>
#include <boost/egg/detail/is_placeholder.hpp>
#include <boost/egg/detail/nest_impl.hpp>
#include <boost/egg/identity.hpp>
#include <boost/egg/preprocessor/cat3.hpp>
#include <boost/egg/result_of.hpp>


namespace boost { namespace egg {


// level0
    template<class Bind = use_default, class Protect = use_default>
    struct X_nest0 :
        X_identity<by_value>
    { };

    typedef X_nest0<>::base_class T_nest0;
    BOOST_EGG_CONST((T_nest0), nest0) = {{}};


// level1-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_EGG_MAX_NEST_LEVEL, <boost/egg/nest.hpp>))
    #include BOOST_PP_ITERATE()


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
#else
#define n BOOST_PP_ITERATION()


    namespace BOOST_EGG_PP_CAT3(nest, n, _detail) {


        template<class Bind, class Protect>
        struct little
        {
#if n != 1
            typedef function<BOOST_EGG_PP_CAT3(nest, BOOST_PP_DEC(n), _detail)::little<Bind, Protect>, by_value> S_nestN_1;
#endif
            typedef BOOST_PP_CAT(details::X_nest_impl, n)<Bind> S_nest_implN;

            template<class Me, class Fun>
            struct apply :
                mpl::eval_if< is_placeholder_<Fun>,
#if n == 1
                    result_of_<Protect(Fun &)>,
#else
                    result_of_<Protect(typename result_of_<S_nestN_1(Fun &)>::type)>,
#endif
                    result_of_<S_nest_implN(Fun &)>
                >
            { };

            template<class Re, class Fun>
            Re call(Fun fun, typename enable_if_< is_placeholder_<Fun> >::type = 0) const
            {
#if n == 1
                return Protect()(fun);
#else
                return Protect()(S_nestN_1()(fun));
#endif
            }

            template<class Re, class Fun>
            Re call(Fun fun, typename disable_if_<is_placeholder_<Fun> >::type = 0) const
            {
                return S_nest_implN()(fun);
            }
        };


    } // namespace nestN_detail


    template<class Bind = use_default, class Protect = use_default>
    struct BOOST_PP_CAT(X_nest, n) : details::derived_from <
        function<
            BOOST_EGG_PP_CAT3(nest, n, _detail)::little<
                typename details::if_use_default<Bind, T_bll_bind>::type,
                typename details::if_use_default<Protect, T_bll_protect>::type
            >,
            by_value
        > >
    { };

    typedef BOOST_PP_CAT(X_nest, n)<>::base_class BOOST_PP_CAT(T_nest, n);
    BOOST_EGG_CONST((BOOST_PP_CAT(T_nest, n)), BOOST_PP_CAT(nest, n)) = {{}};


#undef  n
#endif
