#ifndef BOOST_PP_IS_ITERATING


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(PSTADE_EGG_CONSTRUCT_XXX_PARAMS)
    #error Please define PSTADE_EGG_CONSTRUCT_XXX_PARAMS.
#endif
#define PSTADE_name   BOOST_PP_TUPLE_ELEM(2, 0, PSTADE_EGG_CONSTRUCT_XXX_PARAMS)
#define PSTADE_return BOOST_PP_TUPLE_ELEM(2, 1, PSTADE_EGG_CONSTRUCT_XXX_PARAMS)


    namespace pstade { namespace egg {


        namespace BOOST_PP_CAT(PSTADE_name, _detail) {


            template<class T, class Strategy>
            struct little
            {
                typedef T nullary_result_type;

                template<class Myself, PSTADE_EGG_APPLY_DECL_PARAMS(PSTADE_EGG_MAX_LINEAR_ARITY, A)>
                struct apply
                {
                    typedef T type;
                };

                #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/detail/construct_xxx_include.hpp>))
                #include BOOST_PP_ITERATE()
            };


        } // namespace BOOST_PP_CAT(PSTADE_name, _detail)


        template<class T = unspecified, class Strategy = by_perfect>
        struct BOOST_PP_CAT(X_, PSTADE_name) :
            function<BOOST_PP_CAT(PSTADE_name, _detail)::little<T, Strategy>, Strategy>
        { };

        template< >
        struct BOOST_PP_CAT(X_, PSTADE_name)< >
        {
            template<class T, class Strategy>
            struct apply
            {
                typedef BOOST_PP_CAT(X_, PSTADE_name)<T, Strategy> type;
            };
        };


    } } // namespace pstade::egg


    PSTADE_EGG_REGISTER_NULLARY_RESULT_OF_TEMPLATE(pstade::egg::BOOST_PP_CAT(X_, PSTADE_name), (class)(class))


#undef  PSTADE_return
#undef  PSTADE_name
#undef  PSTADE_EGG_CONSTRUCT_XXX_PARAMS


#else
#define n BOOST_PP_ITERATION()


    template<class Result BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        PSTADE_return(Result, x, PSTADE_EGG_FORWARDING_ARGS(n, a, Strategy const))
    }


#undef  n
#endif
