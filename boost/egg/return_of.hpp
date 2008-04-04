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


#include <boost/mpl/limits/arity.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/egg/preprocessor/enum_params_with.hpp>
#include <boost/egg/result_of.hpp>


namespace boost { namespace egg {


    template<class Fun, BOOST_EGG_PP_ENUM_PARAMS_WITH(BOOST_PP_INC(BOOST_RESULT_OF_NUM_ARGS), class A, = void)>
    struct return_of;


    namespace return_of_detail {


        // See: "Quick-n-Dirty Type Categorization" at Boost.Proto doc.

        template<class T, class Void = void>
        struct arg_
        {
            typedef T type;
        };

        template<class T>
        struct arg_<T, typename T::boost_egg_return_of>
        {
            typedef typename T::type type;
        };


    } // namespace return_of_detail


    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_RESULT_OF_NUM_ARGS, <boost/egg/return_of.hpp>))
    #include BOOST_PP_ITERATE()


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Fun BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)>
    struct return_of<Fun BOOST_PP_ENUM_TRAILING_PARAMS(n, A)> :
        result_of_<
            typename boost::remove_reference<Fun>::type(
                BOOST_EGG_PP_ENUM_PARAMS_WITH(n, typename return_of_detail::arg_<A, >::type)
            )
        >
    {
        typedef void boost_egg_return_of;
    };


#undef  n
#endif
