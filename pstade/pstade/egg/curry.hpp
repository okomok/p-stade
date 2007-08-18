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
#include <pstade/pass_by.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./config.hpp" // PSTADE_EGG_MAX_ARITY
#include "./detail/bind.hpp"
#include "./function.hpp"


namespace pstade { namespace egg {


// 1ary
    struct baby_curry1
    {
        template<class Myself, class Function1>
        struct apply :
            pass_by_value<Function1>
        { };

        template<class Result, class Function1>
        Result call(Function1& fun1) const
        {
            return fun1;
        }
    };

    typedef function<baby_curry1> op_curry1;
    PSTADE_POD_CONSTANT((op_curry1), curry1) = {{}};


// 2ary-
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_EGG_MAX_ARITY, <pstade/egg/curry.hpp>))
    #include BOOST_PP_ITERATE()


} } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    struct BOOST_PP_CAT(baby_curry, n)
    {
        template<class Myself, class Function>
        struct apply :
            result_of<
                BOOST_PP_CAT(op_curry, BOOST_PP_DEC(n))(
                    typename result_of<
                        detail::op_bind(detail::op_bind const&, Function&)
                    >::type
                )
            >
        { };

        template<class Result, class Function>
        Result call(Function& fun) const
        {
            // curry3(bind(bind, fun4))(a1)(a2)(a3)(a4)
            // => bind(bind, fun4)(a1, a2, a3)(a4)
            // => bind(fun4, a1, a2, a3)(a4)
            // => fun4(a1, a2, a3, a4)
            return BOOST_PP_CAT(curry, BOOST_PP_DEC(n))(
                detail::bind(detail::bind, fun)
            );
        }
    };

    typedef function<BOOST_PP_CAT(baby_curry, n)> BOOST_PP_CAT(op_curry, n);
    PSTADE_POD_CONSTANT((BOOST_PP_CAT(op_curry, n)), BOOST_PP_CAT(curry, n)) = {{}};


#undef n
#endif
