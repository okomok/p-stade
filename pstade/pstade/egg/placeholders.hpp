

// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PP_IS_ITERATING


    #ifndef PSTADE_EGG_PLACEHOLDERS_HPP
    #define PSTADE_EGG_PLACEHOLDERS_HPP
    #include "./detail/prefix.hpp"


    #include <boost/mpl/bool.hpp>
    #include <boost/preprocessor/arithmetic/dec.hpp>
    #include <boost/preprocessor/cat.hpp>
    #include <boost/preprocessor/iteration/iterate.hpp>
    #include <boost/preprocessor/repetition/enum.hpp>
    #include <boost/preprocessor/repetition/enum_binary_params.hpp>
    #include <boost/preprocessor/repetition/enum_params.hpp>
    #include <boost/preprocessor/slot/slot.hpp>
    #include <pstade/pod_constant.hpp>
    #include "./apply_decl.hpp"
    #include "./by_perfect.hpp"
    #include "./config.hpp"
    #include "./is_bind_expression.hpp"


    namespace pstade { namespace egg {


        #define PSTADE_EGG_PLACEHOLDER {{}}


        // 1ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_ARITY, <pstade/egg/placeholders.hpp>))
        #include BOOST_PP_ITERATE()


    } } // namespace pstade::egg


    #endif // PSTADE_EGG_PLACEHOLDERS_HPP


#elif BOOST_PP_ITERATION_DEPTH() == 1


    #define  BOOST_PP_VALUE BOOST_PP_ITERATION()
    #include BOOST_PP_ASSIGN_SLOT(1)
    #define n BOOST_PP_SLOT(1)


        struct BOOST_PP_CAT(placeholder, n)
        {
            // nary - PSTADE_EGG_MAX_ARITYary
            template<class Myself, PSTADE_EGG_APPLY_DECL_PARAMS(PSTADE_EGG_MAX_ARITY, A)>
            struct PSTADE_EGG_APPLY_DECL;

            #define  BOOST_PP_ITERATION_PARAMS_2 (3, (n, PSTADE_EGG_MAX_ARITY, <pstade/egg/placeholders.hpp>))
            #include BOOST_PP_ITERATE()
        };


        typedef function<BOOST_PP_CAT(placeholder, n), by_perfect> BOOST_PP_CAT(T_placeholder, n);
        PSTADE_POD_CONSTANT((BOOST_PP_CAT(T_placeholder, n)), BOOST_PP_CAT(placeholder, n)) = PSTADE_EGG_PLACEHOLDER;

        namespace placeholders {
            typedef BOOST_PP_CAT(T_placeholder, n) BOOST_PP_CAT(TT_, n);
            PSTADE_POD_CONSTANT((BOOST_PP_CAT(TT_, n)), BOOST_PP_CAT(_, n)) = PSTADE_EGG_PLACEHOLDER;
        }

        template< >
        struct is_bind_expression< BOOST_PP_CAT(T_placeholder, n) > :
            boost::mpl::true_
        { };


    #undef n


#elif BOOST_PP_ITERATION_DEPTH() == 2


    #define m BOOST_PP_ITERATION()


        template<class Myself, BOOST_PP_ENUM_PARAMS(m, class A)>
        struct apply<Myself, BOOST_PP_ENUM_PARAMS(m, A)>
        {
            typedef BOOST_PP_CAT(A, BOOST_PP_DEC(n)) & type;
        };

        template<class Result, BOOST_PP_ENUM_PARAMS(m, class A)>
        Result call(BOOST_PP_ENUM_BINARY_PARAMS(m, A, & a)) const
        {
            return BOOST_PP_CAT(a, BOOST_PP_DEC(n));
        }


    #undef m


#endif
