

// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PP_IS_ITERATING


    #ifndef BOOST_EGG_ARG_HPP
    #define BOOST_EGG_ARG_HPP
    #include <boost/egg/detail/prefix.hpp>


    #include <boost/mpl/bool.hpp>
    #include <boost/preprocessor/arithmetic/dec.hpp>
    #include <boost/preprocessor/cat.hpp>
    #include <boost/preprocessor/iteration/iterate.hpp>
    #include <boost/preprocessor/repetition/enum_binary_params.hpp>
    #include <boost/preprocessor/repetition/enum_params.hpp>
    #include <boost/egg/apply_decl.hpp>
    #include <boost/egg/by_perfect.hpp>
    #include <boost/egg/config.hpp> // BOOST_EGG_MAX_LINEAR_ARITY
    #include <boost/egg/detail/derived_from.hpp>
    #include <boost/egg/forward.hpp>
    #include <boost/egg/is_bind_expression.hpp>


    namespace boost { namespace egg {


        template<int N, class Strategy = by_perfect>
        struct little_arg;


        template<int N, class Strategy = by_perfect>
        struct X_arg : details::derived_from<
            function<little_arg<N, Strategy>, Strategy> >
        { };

        #define BOOST_EGG_ARG_INIT {{}}


        template<int N, class Strategy>
        struct is_bind_expression< X_arg<N, Strategy> > :
            mpl::true_
        { };

        template<int N, class Strategy>
        struct is_bind_expression< function<little_arg<N, Strategy>, Strategy> > :
            mpl::true_
        { };


        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_EGG_MAX_LINEAR_ARITY, <boost/egg/arg.hpp>))
        #include BOOST_PP_ITERATE()


    } } // namespace boost::egg


    namespace boost {


        template<class T>
        struct is_placeholder;

        template<int N, class Strategy>
        struct is_placeholder< egg::X_arg<N, Strategy> >
        {
    	    enum _vt { value = N };
        };

        template<int N, class Strategy>
        struct is_placeholder< egg::function<egg::little_arg<N, Strategy>, Strategy> >
        {
    	    enum _vt { value = N };
        };


    } // namespace boost


    #include <boost/egg/detail/suffix.hpp>
    #endif // BOOST_EGG_ARG_HPP


#elif BOOST_PP_ITERATION_DEPTH() == 1


    #define  BOOST_PP_VALUE BOOST_PP_ITERATION()
    #include BOOST_PP_ASSIGN_SLOT(1)
    #define n BOOST_PP_SLOT(1)


        template<class Strategy>
        struct little_arg< n, Strategy >
        {
            // nary - BOOST_EGG_MAX_ARITYary
            template<class Me, BOOST_EGG_APPLY_DECL_PARAMS(BOOST_EGG_MAX_LINEAR_ARITY, A)>
            struct BOOST_EGG_APPLY_DECL;

            #define  BOOST_PP_ITERATION_PARAMS_2 (3, (n, BOOST_EGG_MAX_LINEAR_ARITY, <boost/egg/arg.hpp>))
            #include BOOST_PP_ITERATE()
        };


    #undef  n


#elif BOOST_PP_ITERATION_DEPTH() == 2


    #define m BOOST_PP_ITERATION()


        template<class Me, BOOST_PP_ENUM_PARAMS(m, class A)>
        struct apply<Me, BOOST_PP_ENUM_PARAMS(m, A)> :
            result_of_forwarding<Strategy const, m, BOOST_PP_DEC(n), BOOST_PP_CAT(A, BOOST_PP_DEC(n))>
        { };

        template<class Re, BOOST_PP_ENUM_PARAMS(m, class A)>
        Re call(BOOST_PP_ENUM_BINARY_PARAMS(m, A, &a)) const
        {
            return egg::forwarding<Strategy const, m, BOOST_PP_DEC(n)>(BOOST_PP_CAT(a, BOOST_PP_DEC(n)));
        }


    #undef  m


#endif
