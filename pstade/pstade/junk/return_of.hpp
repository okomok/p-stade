#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_RETURN_OF_HPP
#define PSTADE_RETURN_OF_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>


namespace pstade {


    template<class FunCall>
    struct return_of;


    namespace return_of_detail {


        template<class A>
        struct aux_
        {
            typedef A type;
        };

        template<class FunCall>
        struct aux_< return_of<FunCall> > :
            return_of<FunCall>
        { };


    } // namespace return_of_detail


    // 0ary
    template<class Fun>
    struct return_of<Fun(void)> :
        result_of<Fun()>
    { };


    // 1ary-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_RESULT_OF_NUM_ARGS, <pstade/return_of.hpp>))
    #include BOOST_PP_ITERATE()


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Fun, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct return_of<Fun(BOOST_PP_ENUM_PARAMS(n, A))> :
        result_of<
            Fun(PSTADE_PP_ENUM_PARAMS_WITH(n, typename return_of_detail::aux_<A, >::type))
        >
    { };


#undef n
#endif
