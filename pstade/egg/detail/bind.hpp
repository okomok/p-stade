

// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PP_IS_ITERATING


    #ifndef PSTADE_EGG_DETAIL_BIND_HPP
    #define PSTADE_EGG_DETAIL_BIND_HPP
    #include "./detail/prefix.hpp"


    #include <boost/preprocessor/arithmetic/dec.hpp>
    #include <boost/preprocessor/cat.hpp>
    #include <boost/preprocessor/iteration/iterate.hpp>
    #include <boost/preprocessor/repetition/enum.hpp>
    #include <boost/preprocessor/repetition/enum_binary_params.hpp>
    #include <boost/preprocessor/repetition/enum_params.hpp>
    #include <boost/preprocessor/repetition/repeat.hpp>
    #include <pstade/pass_by.hpp>
    #include <pstade/pod_constant.hpp>
    #include <pstade/preprocessor.hpp>
    #include <pstade/result_of.hpp>
    #include "./apply_params.hpp"
    #include "../by_cref.hpp"
    #include "../by_perfect.hpp"
    #include "../config.hpp" // PSTADE_EGG_MAX_ARITY
    #include "./bound_arg.hpp"


    namespace pstade { namespace egg { namespace detail {


        // 1ary-
    #define PSTADE_arg(Z, N, _) BOOST_PP_CAT(Arg, N) BOOST_PP_CAT(m_arg, N);
    #define PSTADE_max_arity BOOST_PP_DEC(PSTADE_EGG_MAX_LINEAR_ARITY)
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_max_arity, <pstade/egg/bind.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_max_arity
    #undef  PSTADE_arg


    } } } // namespace pstade::egg::detail


    #endif // PSTADE_EGG_BIND_HPP


#elif BOOST_PP_ITERATION_DEPTH() == 1


    #define n BOOST_PP_ITERATION()


    #if n == 0


    #else

        template<class Base, BOOST_PP_ENUM_PARAMS(n, class Arg)>
        struct PSTADE_PP_CAT3(baby_bind, n, _result)
        {
            Base m_base;
            BOOST_PP_REPEAT(n, PSTADE_arg, ~)

            typedef Base base_type;

            Base base() const
            {
                return m_base;
            }

            typedef typename
                result_of<Base const(
                    BOOST_PP_ENUM_PARAMS(n, typename result_of<T_eval_if_bind_exprssion(Base const&)>::type()>::type BOOST_PP_INTERCEPT)     
                )>::type
            nullary_result_type;

            template<class Result>
            Result call() const
            {
                return m_base(
                    BOOST_PP_ENUM_PARAMS(n, eval_if_bind_exprssion(m_base)() BOOST_PP_INTERCEPT)
                );
            }

            template<class Myself, PSTADE_EGG_APPLY_PARAMS(n, A)>
            struct apply { };

            // 1ary - nary
        #define PSTADE_meta_eval(Z, N, _) typename result_of<T_eval_if_bind_expression(BOOST_PP_CAT(Arg, n))>::type(BOOST_PP_ENUM_PARAMS(m, A))
        #define PSTADE_eval(Z, N, _) eval_if_bind_expression(BOOST_PP_CAT(m_arg, n))(BOOST_PP_ENUM_PARAMS(m, a))
            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, n, <pstade/egg/bind.hpp>))
            #include BOOST_PP_ITERATE()
        #undef  PSTADE_eval
        #undef  PSTADE_meta_eval
        };

    #endif


        template<class Base, BOOST_PP_ENUM_PARAMS(n, class Arg)>
        struct BOOST_PP_CAT(result_of_bind, n)
        {
            typedef
                function<
                    PSTADE_PP_CAT3(baby_bind, n, _result)<
                        Base,
                        BOOST_PP_ENUM_PARAMS(n, Arg)
                    >,
                    by_perfect
                >
            type;
        }


        #define PSTADE_EGG_BIND_L { {
        #define PSTADE_EGG_BIND_R } }


        struct BOOST_PP_CAT(baby_bind, n)
        {
            template<class Myself, class Base, BOOST_PP_ENUM_PARAMS(n, class Arg)>
            struct apply :
                BOOST_PP_CAT(result_of_bind, n)<
                    typename pass_by_value<Base>::type,
                    PSTADE_PP_ENUM_PARAMS_WITH(n, typename bound_arg<Arg, >::type)
                >
            { };

            template<class Result, class Base, BOOST_PP_ENUM_PARAMS(n, class Arg)>
            Result call(Base& base, BOOST_PP_ENUM_BINARY_PARAMS(n, Arg, & arg)) const
            {
                Result r = PSTADE_EGG_BIND_L base, BOOST_PP_ENUM_PARAMS(n, arg) PSTADE_EGG_BIND_R;
                return r;
            }
        };

        typedef function<BOOST_PP_CAT(baby_bind, n), by_cref> BOOST_PP_CAT(T_bind, n);
        PSTADE_POD_CONSTANT((BOOST_PP_CAT(T_bind, n)), BOOST_PP_CAT(bind, n)) = PSTADE_EGG_DETAIL_BINDX_INIT;


    #undef n


#elif BOOST_PP_ITERATION_DEPTH() == 2


    #define m BOOST_PP_ITERATION()


        template<class Myself, BOOST_PP_ENUM_PARAMS(m, class A)>
        struct apply :
            result_of<Base const(
                BOOST_PP_ENUM(m, PSTADE_meta_eval, ~)
            )>
        { };

        template<class Result, BOOST_PP_ENUM_PARAMS(m, class A)>
        Result call(BOOST_PP_ENUM_BINARY_PARAMS(m, A, & a) const
        {
            return m_base(
                BOOST_PP_ENUM(m, PSTADE_eval, ~)
            );
        }


    #undef m


#endif
