#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_BIND_HPP
#define PSTADE_EGG_DETAIL_BIND_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Assume f3 is a 3ary function:
//   bind(f3, a1, a2)(a3)
//     is equivalent to f3(a1, a2, a3).


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include "../apply_params.hpp"
#include "../config.hpp" // PSTADE_EGG_MAX_ARITY
#include "../function.hpp"
#include "./baby_bind_result.hpp"
#include "./unwrap_ref.hpp"


namespace pstade { namespace egg { namespace detail {


    struct baby_bind
    {
    // 1ary-
        template<class Myself, class Base, PSTADE_EGG_APPLY_PARAMS(A)>
        struct apply { };

    #define PSTADE_max_arity BOOST_PP_DEC(PSTADE_EGG_MAX_ARITY)
    #define PSTADE_unwrap(Z, N, _) , detail::unwrap_ref(BOOST_PP_CAT(a, N))
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_ARITY, <pstade/egg/detail/bind.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_unwrap
    #undef  PSTADE_max_arity
    };


    typedef function<baby_bind> op_bind;
    PSTADE_POD_CONSTANT((op_bind), bind) = {{}};


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Myself, class Base, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, Base, BOOST_PP_ENUM_PARAMS(n, A)>
    {
        typedef
            function<
                PSTADE_PP_CAT3(baby_bind, n, _result)<
                    typename pass_by_value<Base>::type,
                    PSTADE_PP_ENUM_PARAMS_WITH(n, typename unwrapped_of<A, >::type)
                >
            >
        type;
    };

    template<class Result, class Base, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(Base& base, BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        Result r = { { base BOOST_PP_REPEAT(n, PSTADE_unwrap, ~) } };
        return r;
    }


#undef n
#endif
