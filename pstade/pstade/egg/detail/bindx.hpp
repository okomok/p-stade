#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_BINDX_HPP
#define PSTADE_EGG_DETAIL_BINDX_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// bindx means bind2,bind3,...
//
// bind3(f, a1, a2, a3)(a4)
//   is equivalent to f(a1, a2, a3, a4).
// bind3(f, a1, a2, a3) returns a 1ary function object.
// The arity could be more, but not required to implement currying.


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include "../by_cref.hpp"
#include "../by_perfect.hpp"
#include "../config.hpp" // PSTADE_EGG_MAX_ARITY
#include "./bound_arg.hpp"


namespace pstade { namespace egg { namespace detail {


    #define PSTADE_EGG_DETAIL_BINDX_INIT {{}}


    // 2ary-
#define PSTADE_arg(Z, N, _) BOOST_PP_CAT(Arg, N) BOOST_PP_CAT(m_arg, N);
#define PSTADE_max_arity BOOST_PP_DEC(PSTADE_EGG_MAX_ARITY)
    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_max_arity, <pstade/egg/detail/bindx.hpp>))
    #include BOOST_PP_ITERATE()
#undef  PSTADE_max_arity
#undef  PSTADE_arg


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Base, BOOST_PP_ENUM_PARAMS(n, class Arg)>
    struct PSTADE_PP_CAT3(baby_bind, n, _result)
    {
        Base m_base;
        BOOST_PP_REPEAT(n, PSTADE_arg, ~)

        typedef Base base_type;

        Base base() const
        {
            return m_base;
        }

        template<class Myself, class ArgZ>
        struct apply :
            result_of<
                Base const(
                    PSTADE_PP_ENUM_PARAMS_WITH(n, Arg, const&),
                    ArgZ&
                )
            >
        { };

        template<class Result, class ArgZ>
        Result call(ArgZ& argZ) const
        {
            return m_base(
                BOOST_PP_ENUM_PARAMS(n, m_arg),
                argZ
            );
        }
    };


    struct BOOST_PP_CAT(baby_bind, n)
    {
        template<class Myself, class Base, BOOST_PP_ENUM_PARAMS(n, class A)>
        struct apply
        {
            typedef
                function<
                    PSTADE_PP_CAT3(baby_bind, n, _result)<
                        typename pass_by_value<Base>::type,
                        PSTADE_PP_ENUM_PARAMS_WITH(n, typename bound_arg<A, >::type)
                    >,
                    by_perfect
                >
            type;
        };

        template<class Result, class Base, BOOST_PP_ENUM_PARAMS(n, class A)>
        Result call(Base& base, BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
        {
            Result r = { { base, BOOST_PP_ENUM_PARAMS(n, a) } };
            return r;
        }
    };

    typedef function<BOOST_PP_CAT(baby_bind, n), by_cref> BOOST_PP_CAT(T_bind, n);
    PSTADE_POD_CONSTANT((BOOST_PP_CAT(T_bind, n)), BOOST_PP_CAT(bind, n)) = PSTADE_EGG_DETAIL_BINDX_INIT;


#undef n
#endif
