

// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PP_IS_ITERATING


    #ifndef PSTADE_EGG_ARG_HPP
    #define PSTADE_EGG_ARG_HPP
    #include "./detail/prefix.hpp"


    #include <boost/mpl/bool.hpp>
    #include <boost/preprocessor/arithmetic/dec.hpp>
    #include <boost/preprocessor/cat.hpp>
    #include <boost/preprocessor/iteration/iterate.hpp>
    #include <boost/preprocessor/repetition/enum_binary_params.hpp>
    #include <boost/preprocessor/repetition/enum_params.hpp>
    #include "./apply_decl.hpp"
    #include "./by_perfect.hpp"
    #include "./config.hpp" // PSTADE_EGG_MAX_ARITY
    #include "./is_bind_expression.hpp"


    namespace pstade { namespace egg {


        template<int N>
        struct little_arg;


        template<int N>
        struct X_arg :
            function<little_arg<N>, by_perfect>
        { };

        #define PSTADE_EGG_ARG_INIT {{}}


        template<int N>
        struct is_bind_expression< X_arg<N> > :
            boost::mpl::true_
        { };

        template<int N>
        struct is_bind_expression< function<little_arg<N>, by_perfect> > :
            boost::mpl::true_
        { };


        // 1ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_ARITY, <pstade/egg/arg.hpp>))
        #include BOOST_PP_ITERATE()


    } } // namespace pstade::egg


    namespace boost {


        template<class T>
        struct is_placeholder;

        template<int N>
        struct is_placeholder< pstade::egg::X_arg<N> >
        {
    	    enum _vt { value = N };
        };

        template<int N>
        struct is_placeholder< pstade::egg::function<pstade::egg::little_arg<N>, pstade::egg::by_perfect> >
        {
    	    enum _vt { value = N };
        };


    } // namespace boost


    #endif // PSTADE_EGG_ARG_HPP


#elif BOOST_PP_ITERATION_DEPTH() == 1


    #define  BOOST_PP_VALUE BOOST_PP_ITERATION()
    #include BOOST_PP_ASSIGN_SLOT(1)
    #define n BOOST_PP_SLOT(1)


        template< >
        struct little_arg< n >
        {
            // nary - PSTADE_EGG_MAX_ARITYary
            template<class Myself, PSTADE_EGG_APPLY_DECL_PARAMS(PSTADE_EGG_MAX_ARITY, A)>
            struct PSTADE_EGG_APPLY_DECL;

            #define  BOOST_PP_ITERATION_PARAMS_2 (3, (n, PSTADE_EGG_MAX_ARITY, <pstade/egg/arg.hpp>))
            #include BOOST_PP_ITERATE()
        };


    #undef  n


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


    #undef  m


#endif
