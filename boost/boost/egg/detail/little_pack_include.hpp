#ifndef BOOST_PP_IS_ITERATING


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(BOOST_EGG_LITTLE_PACK_TEMPLATE)
    #error Please define BOOST_EGG_LITTLE_PACK_TEMPLATE(N).
#endif
#if !defined(BOOST_EGG_LITTLE_PACK_MAX_ARITY)
    #error Please define BOOST_EGG_LITTLE_PACK_MAX_ARITY.
#endif


    struct little_pack
    {
    // 0ary
        typedef BOOST_EGG_LITTLE_PACK_TEMPLATE(0)<> nullary_result_type;

        template<class Result>
        Result call() const
        {
            return Result();
        }

    // 1ary-
        template<class Myself, BOOST_EGG_APPLY_DECL_PARAMS(BOOST_EGG_LITTLE_PACK_MAX_ARITY, A)>
        struct BOOST_EGG_APPLY_DECL;

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, BOOST_EGG_LITTLE_PACK_MAX_ARITY, <boost/egg/detail/little_pack_include.hpp>))
        #include BOOST_PP_ITERATE()
    };


#undef  BOOST_EGG_LITTLE_PACK_MAX_ARITY
#undef  BOOST_EGG_LITTLE_PACK_TEMPLATE


#else
#define n BOOST_PP_ITERATION()


    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)>
    {
        typedef BOOST_EGG_LITTLE_PACK_TEMPLATE(n)<PSTADE_PP_ENUM_PARAMS_WITH(n, A, &)> type;
    };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return Result(BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef n
#endif
