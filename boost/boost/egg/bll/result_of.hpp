

// Copyright 2004, 2005, 2006 Cryolite.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Copyright Yusuke Kajimoto 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_LAMBDA_RESULT_OF_HPP
#define BOOST_LAMBDA_RESULT_OF_HPP


#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/tuple/tuple.hpp>


#if !defined(BOOST_LAMBDA_RESULT_OF_MAX_ARITY)
#define BOOST_LAMBDA_RESULT_OF_MAX_ARITY 3
#endif


namespace boost {


    template<class F>
    struct result_of;


    namespace lambda {

        template<class T>
        class lambda_functor;

    }


    namespace lambda_result_of_detail {

        // rvalue
        template<class A>
        struct to_ref
        {
            typedef A const &type;
        };

        // lvalue
        template<class A>
        struct to_ref<A &>
        {
            typedef A &type;
        };

    }


// 0ary
    template<class T>
    struct result_of<lambda::lambda_functor<T>(void)>
    {
        typedef typename lambda::lambda_functor<T>::nullary_return_type type;
    };

    template<class T>
    struct result_of<lambda::lambda_functor<T> const(void)> :
        result_of<lambda::lambda_functor<T>(void)>
    { };


// 1ary-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_LAMBDA_RESULT_OF_MAX_ARITY, <boost/egg/bll/result_of.hpp>))
    #include BOOST_PP_ITERATE()


} // namespace boost


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class T, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct result_of<lambda::lambda_functor<T>(BOOST_PP_ENUM_PARAMS(n, A))> :
        T::template sig<
            tuples::tuple<
                BOOST_PP_ENUM_BINARY_PARAMS(n, typename lambda_result_of_detail::to_ref<A, >::type BOOST_PP_INTERCEPT)
            >
        >
    { };

    template<class T, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct result_of<lambda::lambda_functor<T> const(BOOST_PP_ENUM_PARAMS(n, A))> :
        result_of<lambda::lambda_functor<T>(BOOST_PP_ENUM_PARAMS(n, A))>
    { };


#undef n
#endif
