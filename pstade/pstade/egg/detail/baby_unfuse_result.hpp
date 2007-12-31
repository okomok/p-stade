#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_BABY_UNFUSE_RESULT_HPP
#define PSTADE_EGG_DETAIL_BABY_UNFUSE_RESULT_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This could be implementedy by 'compose' with 'tuple_pack',
// but this is the basis together with 'fuse'.


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include <pstade/use_default.hpp>
#include "../baby_apply.hpp"
#include "../by_ref.hpp"
#include "../tuple/config.hpp"
#include "../tuple/pack.hpp"
#include "./use_nullary_result.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Base, class Pack>
    struct nullary_result_of :
        result_of<
            Base const(typename result_of<Pack const()>::type)
        >
    { };


    // If 'NullaryResult' is 'boost::use_default', this is not nullary-callable.
    // Else if 'NullaryResult' is 'use_nullary_result', 'Base' is considered
    // as callable with an empty tuple, then the result is inspected.
    // Otherwise, a passed type is the result type of this.

    template<class Base, class Pack, class NullaryResult>
    struct baby_unfuse_result
    {
        typedef Base base_type;

        typedef typename
            if_use_default<Pack,
                typename X_tuple_pack<by_ref>::function_type
            >::type
        pack_type;

        Base m_base;
        pack_type m_pack;

        Base base() const
        {
            return m_base;
        }

    // 0ary
        typedef typename
            eval_if_use_nullary_result<NullaryResult,
                nullary_result_of<Base, pack_type>
            >::type
        nullary_result_type;

        template<class Result>
        Result call() const
        {
            return m_base(m_pack());
        }

    // 1ary-
        template<class Myself, PSTADE_EGG_BABY_APPLY_PARAMS(PSTADE_EGG_TUPLE_MAX_SIZE, A)>
        struct PSTADE_EGG_BABY_APPLY_DECL;

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_TUPLE_MAX_SIZE, <pstade/egg/detail/baby_unfuse_result.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } } // namespace pstade::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
        result_of<
            Base const(typename result_of<pack_type const(PSTADE_PP_ENUM_PARAMS_WITH(n, A, &))>::type)
        >
    { };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return m_base(m_pack(BOOST_PP_ENUM_PARAMS(n, a)));
    }


#undef n
#endif
