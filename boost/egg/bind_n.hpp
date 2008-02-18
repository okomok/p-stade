

// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PP_IS_ITERATING


    #ifndef BOOST_EGG_BIND_N_HPP
    #define BOOST_EGG_BIND_N_HPP
    #include <boost/egg/detail/prefix.hpp>


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
    #include <boost/egg/apply_decl.hpp>
    #include <boost/egg/by_perfect.hpp>
    #include <boost/egg/by_value.hpp>
    #include <boost/egg/config.hpp>
    #include <boost/egg/const.hpp>
    #include <boost/egg/detail/boost_use_default_fwd.hpp>
    #include <boost/egg/detail/derived_from.hpp>
    #include <boost/egg/detail/pp_cat3.hpp>
    #include <boost/egg/detail/pp_enum_params_with.hpp>
    #include <boost/egg/detail/substitute.hpp>
    #include <boost/egg/detail/use_nullary_result.hpp>
    #include <boost/egg/is_bind_expression.hpp>
    #include <boost/egg/result_of_ref.hpp>


    namespace boost { namespace egg {


        #define BOOST_EGG_BIND_L { {
        #define BOOST_EGG_BIND_R } }


    #define BOOST_EGG_arg(Z, N, _) BOOST_PP_CAT(Arg, N) BOOST_PP_CAT(m_arg, N);
    #define BOOST_EGG_max_arity BOOST_PP_DEC(BOOST_EGG_MAX_LINEAR_ARITY)
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_EGG_max_arity, <boost/egg/bind_n.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  BOOST_EGG_max_arity
    #undef  BOOST_EGG_arg


    } } // namespace boost::egg


    #include <boost/egg/detail/suffix.hpp>
    #endif // BOOST_EGG_BIND_N_HPP


#elif BOOST_PP_ITERATION_DEPTH() == 1


    #define  BOOST_PP_VALUE BOOST_PP_ITERATION()
    #include BOOST_PP_ASSIGN_SLOT(1)
    #define n BOOST_PP_SLOT(1)


        template<class Base, class NullaryResult BOOST_PP_ENUM_TRAILING_PARAMS(n, class Arg)>
        struct BOOST_EGG_PP_CAT3(little_bind, n, _result)
        {
            Base m_base;
            BOOST_PP_REPEAT(n, BOOST_EGG_arg, ~)

            Base const &base() const
            {
                return m_base;
            }

            // 0ary - BOOST_EGG_MAX_ARITYary
        #define BOOST_EGG_meta_substitute(Z, N, _) \
            typename result_of_ref< \
                typename result_of_ref< \
                    details::T_substitute(BOOST_PP_CAT(Arg, N) const &) \
                >::type(BOOST_EGG_PP_ENUM_PARAMS_WITH(m, A, &)) \
            >::type \
        /**/
        #define BOOST_EGG_substitute(Z, N, _) \
            details::substitute(BOOST_PP_CAT(m_arg, N))(BOOST_PP_ENUM_PARAMS(m, a)) \
        /**/

            template<class Me, BOOST_EGG_APPLY_DECL_PARAMS(BOOST_EGG_MAX_ARITY, A)>
            struct BOOST_EGG_APPLY_DECL;

            #define  BOOST_PP_ITERATION_PARAMS_2 (3, (0, BOOST_EGG_MAX_ARITY, <boost/egg/bind_n.hpp>))
            #include BOOST_PP_ITERATE()

        #undef  BOOST_EGG_substitute
        #undef  BOOST_EGG_meta_substitute
        };


        template<class Base, class NullaryResult BOOST_PP_ENUM_TRAILING_PARAMS(n, class Arg)>
        struct BOOST_PP_CAT(result_of_bind, n)
        {
            typedef
                function<
                    BOOST_EGG_PP_CAT3(little_bind, n, _result)<
                        Base, NullaryResult BOOST_PP_ENUM_TRAILING_PARAMS(n, Arg)
                    >,
                    by_perfect
                >
            type;
        };


        template<class Base, class NullaryResult BOOST_PP_ENUM_TRAILING_PARAMS(n, class Arg)>
        struct is_bind_expression<
                function<
                    BOOST_EGG_PP_CAT3(little_bind, n, _result)<
                        Base, NullaryResult BOOST_PP_ENUM_TRAILING_PARAMS(n, Arg)
                    >,
                    by_perfect
                >
        > : mpl::true_
        { };


        template<class NullaryResult>
        struct BOOST_PP_CAT(little_bind, n)
        {
            template<class Me, class Base BOOST_PP_ENUM_TRAILING_PARAMS(n, class Arg)>
            struct apply :
                BOOST_PP_CAT(result_of_bind, n)<
                    Base, NullaryResult BOOST_PP_ENUM_TRAILING_PARAMS(n, Arg)
                >
            { };

            template<class Re, class Base BOOST_PP_ENUM_TRAILING_PARAMS(n, class Arg)>
            Re call(Base base BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(n, Arg, arg)) const
            {
                Re r = BOOST_EGG_BIND_L base BOOST_PP_ENUM_TRAILING_PARAMS(n, arg) BOOST_EGG_BIND_R;
                return r;
            }
        };

        template<class NullaryResult = use_default>
        struct BOOST_PP_CAT(X_bind, n) : details::derived_from<
            function<BOOST_PP_CAT(little_bind, n)<NullaryResult>, by_value> >
        { };

        typedef BOOST_PP_CAT(X_bind, n)<>::base_class BOOST_PP_CAT(T_bind, n);
        BOOST_EGG_CONST((BOOST_PP_CAT(T_bind, n)), BOOST_PP_CAT(bind, n)) = {{}};


    #undef  n


#elif BOOST_PP_ITERATION_DEPTH() == 2


    #define m BOOST_PP_ITERATION()


    #if m == 0

        struct extract_nullary_result :
            result_of_ref<
                typename result_of_ref<typename result_of_ref<details::T_substitute(Base &)>::type()>::type // `Base const` in Boost.Bind.
                (
                    BOOST_PP_ENUM(n, BOOST_EGG_meta_substitute, ~)
                )
            >
        { };

        typedef typename
            eval_if_use_nullary_result< NullaryResult,
                extract_nullary_result
            >::type
        nullary_result_type;

    #else

        template<class Me, BOOST_PP_ENUM_PARAMS(m, class A)>
        struct apply<Me, BOOST_PP_ENUM_PARAMS(m, A)> :
            result_of_ref<
                typename result_of_ref<typename result_of_ref<details::T_substitute(Base &)>::type(BOOST_EGG_PP_ENUM_PARAMS_WITH(m, A, &))>::type // `Base const` in Boost.Bind.
                (
                    BOOST_PP_ENUM(n, BOOST_EGG_meta_substitute, ~)
                )
            >
        { };

    #endif

        template<class Re BOOST_PP_ENUM_TRAILING_PARAMS(m, class A)>
        Re call(BOOST_PP_ENUM_BINARY_PARAMS(m, A, &a)) const
        {
            return
                details::substitute(m_base)(BOOST_PP_ENUM_PARAMS(m, a)) // `m_base` in Boost.Bind.
                (
                    BOOST_PP_ENUM(n, BOOST_EGG_substitute, ~)
                );
        }


    #undef m


#endif
