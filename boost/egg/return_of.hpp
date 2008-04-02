#ifndef BOOST_PP_IS_ITERATING
#ifndef BOOST_EGG_RETURN_OF_HPP
#define BOOST_EGG_RETURN_OF_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/egg/detail/in_fun_spec.hpp>
#include <boost/egg/preprocessor/enum_params_with.hpp>
#include <boost/egg/result_of.hpp>


namespace boost { namespace egg {


    template<class Fun>
    struct return_of;


    template<class Fun>
    struct as_arg;


    template<class Arg>
    struct return_of
    {
        typedef Arg type;
    };

    template<class Fun>
    struct return_of< as_arg<Fun> >
    {
        typedef Fun type;
    };


    template<class Arg>
    struct return_of<Arg *> :
        boost::mpl::eval_if< boost::is_function<Arg>, // if decayed
            return_of<Arg>,
            boost::mpl::identity<Arg *>
        >
    { };


    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_RESULT_OF_NUM_ARGS, <boost/egg/return_of.hpp>))
    #include BOOST_PP_ITERATE()


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Fun BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)>
    struct return_of<Fun(BOOST_EGG_ENUM_PARAMS_IN_FUN_SPEC(n, A))> :
        result_of_<
            typename boost::remove_reference<Fun>::type(
                BOOST_EGG_PP_ENUM_PARAMS_WITH(n, typename return_of<A, >::type)
            )
        >
    { };


#undef  n
#endif
