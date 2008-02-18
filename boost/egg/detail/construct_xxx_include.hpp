#ifndef BOOST_PP_IS_ITERATING


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(BOOST_EGG_CONSTRUCT_XXX_PARAMS)
    #error Please define BOOST_EGG_CONSTRUCT_XXX_PARAMS.
#endif
#define name    BOOST_PP_TUPLE_ELEM(2, 0, BOOST_EGG_CONSTRUCT_XXX_PARAMS)
#define return_ BOOST_PP_TUPLE_ELEM(2, 1, BOOST_EGG_CONSTRUCT_XXX_PARAMS)


    namespace boost { namespace egg {


        namespace BOOST_PP_CAT(name, _detail) {


            template<class T, class Strategy>
            struct little
            {
                typedef T nullary_result_type;

                template<class Me, BOOST_EGG_APPLY_DECL_PARAMS(BOOST_EGG_MAX_LINEAR_ARITY, A)>
                struct apply
                {
                    typedef T type;
                };

                #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_EGG_MAX_LINEAR_ARITY, <boost/egg/detail/construct_xxx_include.hpp>))
                #include BOOST_PP_ITERATE()
            };


        } // namespace BOOST_PP_CAT(name, _detail)


        template<class T = unspecified, class Strategy = by_perfect>
        struct BOOST_PP_CAT(X_, name) :
            function<BOOST_PP_CAT(name, _detail)::little<T, Strategy>, Strategy>
        { };

        template< >
        struct BOOST_PP_CAT(X_, name)< >
        {
            template<class T, class Strategy>
            struct apply
            {
                typedef BOOST_PP_CAT(X_, name)<T, Strategy> type;
            };
        };


    } } // namespace boost::egg


    BOOST_EGG_REGISTER_NULLARY_RESULT_OF_TEMPLATE(boost::egg::BOOST_PP_CAT(X_, name), (class)(class))


#undef  return_
#undef  name
#undef  BOOST_EGG_CONSTRUCT_XXX_PARAMS


#else
#define n BOOST_PP_ITERATION()


// 'x' is clearly initialized, but msvc warns for some reason.
#if defined(BOOST_MSVC)
    #pragma warning(push)
    #pragma warning(disable: 4700) // uninitialized local variable 'x' used
#endif

    template<class Re BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)>
    Re call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, &a)) const
    {
        return_(Re, x, BOOST_EGG_FORWARDING_ARGS(n, a, Strategy const))
    }

#if defined(BOOST_MSVC)
    #pragma warning(pop)
#endif


#undef  n
#endif
