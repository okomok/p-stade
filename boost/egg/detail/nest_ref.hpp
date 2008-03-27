#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_DETAIL_NEST_REF_HPP
#define BOOST_EGG_DETAIL_NEST_REF_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/egg/by_perfect.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_MAX_ARITY
#include <boost/egg/const.hpp>
#include <boost/egg/identity.hpp>
#include <boost/egg/preprocessor/cat3.hpp>
#include <boost/egg/result_of.hpp>
#include <boost/egg/detail/derived_from.hpp>
#include <boost/egg/detail/nest.hpp>
#include <boost/egg/detail/ref.hpp>


namespace boost { namespace egg {


// level0
    template<class Bind = use_default>
    struct X_ref0 :
        X_identity<by_perfect>
    { };

    typedef X_ref0<>::base_class T_ref0;
    BOOST_EGG_CONST((T_ref0), ref0) = {{}};


// level1-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_EGG_MAX_ARITY, <boost/egg/detail/nest_ref.hpp>))
    #include BOOST_PP_ITERATE()


} } // namespace boost::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    namespace BOOST_EGG_PP_CAT3(nest_ref, n, _detail) {


        template<class Bind>
        struct little
        {
            typedef BOOST_PP_CAT(X_nest, n)<Bind> S_nestN;

            template<class Me, class A>
            struct apply :
                result_of_<
                    typename result_of_<
                        S_nestN(details::T_unwrap_ref const &)
                    >::type(typename result_of_<details::T_wrap_ref(A&)>::type)
                >
            { };

            template<class Re, class A>
            Re call(A &a) const
            {
                return S_nestN()(details::unwrap_ref)(details::wrap_ref(a));
            }
        };


    } // namespace nest_refN_detail


    template<class Bind = use_default>
    struct BOOST_PP_CAT(X_ref, n) : details::derived_from<
        function<BOOST_EGG_PP_CAT3(nest_ref, n, _detail)::little<Bind>, by_perfect> >
    { };

    typedef BOOST_PP_CAT(X_ref, n)<>::base_class BOOST_PP_CAT(T_ref, n);
    BOOST_EGG_CONST((BOOST_PP_CAT(T_ref, n)), BOOST_PP_CAT(ref, n)) = {{}};


#undef  n
#endif
