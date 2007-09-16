#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_BABY_NAMED_RESULT_HPP
#define PSTADE_EGG_DETAIL_BABY_NAMED_RESULT_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include <pstade/use_default.hpp>
#include "../apply_params.hpp"
#include "../config.hpp"
#include "../lambda/bind.hpp"
#include "./bind1.hpp"


namespace pstade { namespace egg { namespace detail {


// 0ary
    template<class Base>
    struct baby_named0_result
    {
        typedef Base base_type;

        Base m_base;

        Base base() const
        {
            return m_base;
        }

        typedef typename
            result_of<Base const()>::type
        nullary_result_type;

        template<class Result>
        Result call() const
        {
            return m_base();
        }
    };


    template<class Base>
    struct baby_named3_result
    {
        template<class Myself, class A0, class A1, class A2>
        struct apply
        {
        
        };

        template<class Result, class A0, class A1, class A2>
        Result call(A0& a0, A1& a1, A2& a2) const
        {
            typedef boost::tuples::tuple<A0&, A1&> tup_t;
            typedef typename left_indices<tup_t>::type ind_t
            typedef typename foldl<tup_t, add_index_to_arg<ind_t> >::type::tuple_type itup_t;
            itup_t itup(tup_t(a0, a1));
            B0 b0 = a0.m_get();//detail::keywords_to_arg0(a0);
            B1 b1 = a1.m_get(tuple_pack_by_ref(a1));//detail::keywords_to_arg1(b0, a1);
            B2 b2 = a2.m_get(tuple_pack_by_ref(b0, b1));//detail::keywords_to_arg2(b0, b1, a2);
            return m_base(b0, b1, b2);
        }
    };


    // 2ary-
        template<class Myself, PSTADE_EGG_APPLY_PARAMS(PSTADE_EGG_LINEAR_MAX_ARITY, A)>
        struct apply { };

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_EGG_LINEAR_MAX_ARITY, <pstade/egg/detail/baby_named_result.hpp>))
        #include BOOST_PP_ITERATE()

} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
        result_of<
            op_lambda_bind(Base const&, PSTADE_PP_ENUM_PARAMS_WITH(n, A, &))
        >
    { };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return boost::lambda::bind(m_base, BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef n
#endif
