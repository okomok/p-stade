#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_RETURN_OF_HPP
#define PSTADE_EGG_RETURN_OF_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/preprocessor.hpp>
#include "./result_of_ref.hpp"


namespace pstade { namespace egg {


    template<class Fun>
    struct return_of;


    template<class Fun>
    struct F_ptr;


    template<class Arg>
    struct return_of
    {
        typedef Arg type;
    };


    template<class Arg>
    struct return_of<Arg *> :
        boost::mpl::eval_if< boost::is_function<Arg>,
            return_of<Arg>,
            boost::mpl::identity<Arg *>
        >
    { };


    template<class Fun>
    struct return_of< F_ptr<Fun> >
    {
        typedef typename boost::remove_pointer<Fun>::type *type;
    };


    // 0ary
    template<class Fun>
    struct return_of<Fun(void)> :
        result_of_ref<Fun()>
    { };


    // 1ary-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_RESULT_OF_NUM_ARGS, <pstade/egg/return_of.hpp>))
    #include BOOST_PP_ITERATE()


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Fun, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct return_of<Fun(BOOST_PP_ENUM_PARAMS(n, A))> :
        result_of_ref<
            Fun(
                PSTADE_PP_ENUM_PARAMS_WITH(n, typename return_of<A, >::type)
            )
        >
    { };


#undef  n
#endif
