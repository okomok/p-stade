#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_DETAIL_LITTLE_UNCURRY_RESULT_HPP
#define BOOST_EGG_DETAIL_LITTLE_UNCURRY_RESULT_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/egg/apply_decl.hpp>
#include <boost/egg/config.hpp> // BOOST_EGG_MAX_ARITY
#include <boost/egg/forward.hpp>
#include <boost/egg/result_of.hpp>


namespace boost { namespace egg { namespace details {


    template<class Base, class Strategy>
    struct little_uncurry_result
    {
        Base m_base;

        Base const &base() const
        {
            return m_base;
        }

        template<class Me, BOOST_EGG_APPLY_DECL_PARAMS(BOOST_EGG_MAX_ARITY, A)>
        struct BOOST_EGG_APPLY_DECL;

    #define BOOST_EGG_open_result_of(Z, I, _)  typename result_of<
    #define BOOST_EGG_close_result_of(Z, I, _) >::type(typename result_of_forwarding<Strategy const, n, I, BOOST_PP_CAT(A, I)>::type)
    #define BOOST_EGG_paren(Z, I, _) ( egg::forwarding<Strategy const, n, I>(BOOST_PP_CAT(a, I)) )
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_EGG_MAX_ARITY, <boost/egg/detail/little_uncurry_result.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  BOOST_EGG_paren
    #undef  BOOST_EGG_close_result_of
    #undef  BOOST_EGG_open_result_of
    };


} } } // namespace boost::egg::details


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Me, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Me, BOOST_PP_ENUM_PARAMS(n, A)> :
        result_of<
            BOOST_PP_REPEAT_FROM_TO(1, n, BOOST_EGG_open_result_of, ~)
                Base const(typename result_of_forwarding<Strategy const, n, 0, A0>::type)
            BOOST_PP_REPEAT_FROM_TO(1, n, BOOST_EGG_close_result_of, ~)
        >      
    { };

    template<class Re, BOOST_PP_ENUM_PARAMS(n, class A)>
    Re call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, &a)) const
    {
        return m_base BOOST_PP_REPEAT(n, BOOST_EGG_paren, ~) ;
    }


#undef  n
#endif
