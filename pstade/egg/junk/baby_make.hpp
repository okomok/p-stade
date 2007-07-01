#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_BABY_MAKE_HPP
#define PSTADE_EGG_DETAIL_BABY_MAKE_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type.hpp>
#include <pstade/enable_if.hpp>
#include "../apply_params.hpp"
#include "../is_makable.hpp"
#include "./config.hpp" // PSTADE_EGG_MAX_ARITY


namespace pstade { namespace egg { namespace detail {


    template<class X>
    struct baby_make
    {
    // 0ary
        typedef X nullary_result_type;

        template<class Result>
        static Result call_aux(boost::type<Result>, typename disable_if<is_makable<Result> > = 0)
        {
            return Result();
        }

        template<class Result>
        static Result call_aux(boost::type<Result>, typename enable_if<is_makable<Result> > = 0)
        {
            return Result::make();
        }

        template<class Result>
        Result call() const
        {
            return call_aux(boost::type<Result>());
        }

    // 1ary-
        template<class Myself, PSTADE_EGG_APPLY_PARAMS(A)>
        struct apply
        {
            typedef X type;
        };

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_ARITY, <pstade/egg/detail/baby_make.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    static Result call_aux(boost::type<Result>, BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a), typename disable_if<is_makable<X> >::type = 0)
    {
        return Result(BOOST_PP_ENUM_PARAMS(n, a));
    }

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    static Result call_aux(boost::type<Result>, BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a), typename enable_if< is_makable<X> >::type = 0)
    {
        return Result::make(BOOST_PP_ENUM_PARAMS(n, a));
    }

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return call_aux(boost::type<Result>(), BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef n
#endif
