

// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PP_IS_ITERATING


    #ifndef PSTADE_EGG_BIND_N_HPP
    #define PSTADE_EGG_BIND_N_HPP
    #include "./detail/prefix.hpp"


    #include <boost/mpl/bool.hpp>
    #include <boost/preprocessor/arithmetic/dec.hpp>
    #include <boost/preprocessor/cat.hpp>
    #include <boost/preprocessor/facilities/intercept.hpp>
    #include <boost/preprocessor/iteration/iterate.hpp>
    #include <boost/preprocessor/punctuation/comma_if.hpp>
    #include <boost/preprocessor/repetition/enum.hpp>
    #include <boost/preprocessor/repetition/enum_binary_params.hpp>
    #include <boost/preprocessor/repetition/enum_params.hpp>
    #include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
    #include <boost/preprocessor/repetition/enum_trailing_params.hpp>
    #include <boost/preprocessor/repetition/repeat.hpp>
    #include <boost/preprocessor/selection/max.hpp>
    #include <boost/preprocessor/slot/slot.hpp>
    #include <pstade/apple/boost/use_default_fwd.hpp>
    #include <pstade/pass_by.hpp>
    #include <pstade/pod_constant.hpp>
    #include <pstade/preprocessor.hpp>
    #include "./apply_decl.hpp"
    #include "./by_cref.hpp"
    #include "./by_perfect.hpp"
    #include "./config.hpp"
    #include "./detail/bound.hpp"
    #include "./detail/substitute.hpp"
    #include "./detail/use_nullary_result.hpp"
    #include "./is_bind_expression.hpp"
    #include "./result_of_ref.hpp"


    namespace pstade { namespace egg {


        #define PSTADE_EGG_BIND_L { {
        #define PSTADE_EGG_BIND_R } }

        // 0ary-
    #define PSTADE_arg(Z, N, _) BOOST_PP_CAT(Arg, N) BOOST_PP_CAT(m_arg, N);
    #define PSTADE_max_arity BOOST_PP_DEC(PSTADE_EGG_MAX_LINEAR_ARITY)
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, PSTADE_max_arity, <pstade/egg/bind_n.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_max_arity
    #undef  PSTADE_arg


    } } // namespace pstade::egg


    #endif // PSTADE_EGG_BIND_N_HPP


#elif BOOST_PP_ITERATION_DEPTH() == 1


    #define  BOOST_PP_VALUE BOOST_PP_ITERATION()
    #include BOOST_PP_ASSIGN_SLOT(1)
    #define n BOOST_PP_SLOT(1)


        template<class Base, class NullaryResult BOOST_PP_ENUM_TRAILING_PARAMS(n, class Arg)>
        struct PSTADE_PP_CAT3(little_bind, n, _result)
        {
            Base m_base;
            BOOST_PP_REPEAT(n, PSTADE_arg, ~)

            Base const& base() const
            {
                return m_base;
            }

            // 0ary - PSTADE_EGG_MAX_ARITYary
        #define PSTADE_meta_substitute(Z, N, _) \
            typename result_of_ref< \
                typename result_of_ref< \
                    detail::T_substitute(typename detail::unbound<BOOST_PP_CAT(Arg, N)>::type) \
                >::type(PSTADE_PP_ENUM_PARAMS_WITH(m, A, &)) \
            >::type \
        /**/
        #define PSTADE_substitute(Z, N, _) \
            detail::substitute(BOOST_PP_CAT(m_arg, N))(BOOST_PP_ENUM_PARAMS(m, a)) \
        /**/

            template<class Me, PSTADE_EGG_APPLY_DECL_PARAMS(PSTADE_EGG_MAX_ARITY, A)>
            struct PSTADE_EGG_APPLY_DECL;

            #define  BOOST_PP_ITERATION_PARAMS_2 (3, (0, PSTADE_EGG_MAX_ARITY, <pstade/egg/bind_n.hpp>))
            #include BOOST_PP_ITERATE()

        #undef  PSTADE_substitute
        #undef  PSTADE_meta_substitute
        };


        template<class Base, class NullaryResult BOOST_PP_ENUM_TRAILING_PARAMS(n, class Arg)>
        struct BOOST_PP_CAT(result_of_bind, n)
        {
            typedef
                function<
                    PSTADE_PP_CAT3(little_bind, n, _result)<
                        Base, NullaryResult
                        BOOST_PP_ENUM_TRAILING_PARAMS(n, Arg)
                    >,
                    by_perfect
                >
            type;
        };


        template<class Base, class NullaryResult BOOST_PP_ENUM_TRAILING_PARAMS(n, class Arg)>
        struct is_bind_expression<
                function<
                    PSTADE_PP_CAT3(little_bind, n, _result)<
                        Base, NullaryResult
                        BOOST_PP_ENUM_TRAILING_PARAMS(n, Arg)
                    >,
                    by_perfect
                >
        > : boost::mpl::true_
        { };


        template<class NullaryResult>
        struct BOOST_PP_CAT(little_bind, n)
        {
            template<class Me, class Base BOOST_PP_ENUM_TRAILING_PARAMS(n, class Arg)>
            struct apply :
                BOOST_PP_CAT(result_of_bind, n)<
                    typename pass_by_value<Base>::type, NullaryResult BOOST_PP_COMMA_IF(n)
                    PSTADE_PP_ENUM_PARAMS_WITH(n, typename detail::bound<Arg, >::type)
                >
            { };

            template<class Re, class Base BOOST_PP_ENUM_TRAILING_PARAMS(n, class Arg)>
            Re call(Base& base BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(n, Arg, & arg)) const
            {
                Re r = PSTADE_EGG_BIND_L base BOOST_PP_ENUM_TRAILING_PARAMS(n, arg) PSTADE_EGG_BIND_R;
                return r;
            }
        };

        template<class NullaryResult = boost::use_default>
        struct BOOST_PP_CAT(X_bind, n) :
            function<BOOST_PP_CAT(little_bind, n)<NullaryResult>, by_cref>
        { };

        typedef BOOST_PP_CAT(X_bind, n)<>::function_type BOOST_PP_CAT(T_bind, n);
        PSTADE_POD_CONSTANT((BOOST_PP_CAT(T_bind, n)), BOOST_PP_CAT(bind, n)) = {{}};


    #undef  n


#elif BOOST_PP_ITERATION_DEPTH() == 2


    #define m BOOST_PP_ITERATION()


    #if m == 0

        struct nullary_result :
            result_of_ref<
                typename result_of_ref<typename result_of_ref<detail::T_substitute(Base&)>::type()>::type // `Base const` in Boost.Bind.
                (
                    BOOST_PP_ENUM(n, PSTADE_meta_substitute, ~)
                )
            >
        { };

        typedef typename
            eval_if_use_nullary_result<NullaryResult,
                nullary_result
            >::type
        nullary_result_type;

    #else

        template<class Me, BOOST_PP_ENUM_PARAMS(m, class A)>
        struct apply<Me, BOOST_PP_ENUM_PARAMS(m, A)> :
            result_of_ref<
                typename result_of_ref<typename result_of_ref<detail::T_substitute(Base&)>::type(PSTADE_PP_ENUM_PARAMS_WITH(m, A, &))>::type // `Base const` in Boost.Bind.
                (
                    BOOST_PP_ENUM(n, PSTADE_meta_substitute, ~)
                )
            >
        { };

    #endif

        template<class Re BOOST_PP_ENUM_TRAILING_PARAMS(m, class A)>
        Re call(BOOST_PP_ENUM_BINARY_PARAMS(m, A, & a)) const
        {
            return
                detail::substitute(m_base)(BOOST_PP_ENUM_PARAMS(m, a)) // `m_base` in Boost.Bind.
                (
                    BOOST_PP_ENUM(n, PSTADE_substitute, ~)
                );
        }


    #undef m


#endif
