#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_CURRY_HPP
#define PSTADE_EGG_CURRY_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./config.hpp" // PSTADE_EGG_MAX_ARITY
#include "./detail/bind1.hpp"
#include "./detail/bind2_.hpp"
#include "./detail/curry_result_initializers.hpp"
#include "./function.hpp"
#include "./function_by_value.hpp"


namespace pstade { namespace egg {


    // for curry2 implementation
    template<class Base>
    struct result_of_curry1
    {
        typedef Base type;
    };

// 2ary-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_EGG_MAX_ARITY, <pstade/egg/curry.hpp>))
    #include BOOST_PP_ITERATE()


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()
#define n_ BOOST_PP_DEC(n)


    template<class Base>
    struct BOOST_PP_CAT(result_of_curry, n) :
        BOOST_PP_CAT(result_of_curry, n_)<
            function<
                detail::baby_bind1_result<
                    function<detail::BOOST_PP_CAT(baby_bind, n_)>,
                    Base
                >
            >
        >
    { };


    struct BOOST_PP_CAT(baby_curry, n)
    {
        template<class Myself, class Base>
        struct apply :
            BOOST_PP_CAT(result_of_curry, n)<Base>
        { };

        template<class Result, class Base>
        Result call(Base base) const
        {
            Result r = PSTADE_EGG_CURRY_L(n) base PSTADE_EGG_CURRY_R(n);
            return r;
        }

#if 0 // These were used to look into result_of_curryN<>::type.
        template<class Myself, class Base>
        struct apply :
            result_of<
                BOOST_PP_CAT(op_curry, n_)(
                    typename result_of<
                        detail::op_bind1(detail::BOOST_PP_CAT(op_bind, n_) const&, Base&)
                    >::type
                )
            >
        { };

        template<class Result, class Base>
        Result call(Base base) const
        {
            // Assume fun4 is 4ary.
            // curry3(bind1(bind3, fun4))(a1)(a2)(a3)(a4)
            // => bind1(bind3, fun4)(a1, a2, a3)(a4)
            // => bind3(fun4, a1, a2, a3)(a4)
            // => fun4(a1, a2, a3, a4)
            return BOOST_PP_CAT(curry, n_)(
                detail::bind1(detail::BOOST_PP_CAT(bind, n_), base)
            );
        }
#endif
    };


    typedef function_by_value<BOOST_PP_CAT(baby_curry, n)> BOOST_PP_CAT(op_curry, n);
    PSTADE_POD_CONSTANT((BOOST_PP_CAT(op_curry, n)), BOOST_PP_CAT(curry, n)) = {{}};


#undef n_
#undef n
#endif
