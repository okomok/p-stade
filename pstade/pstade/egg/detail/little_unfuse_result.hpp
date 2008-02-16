#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_LITTLE_UNFUSE_RESULT_HPP
#define PSTADE_EGG_DETAIL_LITTLE_UNFUSE_RESULT_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This could be implementedy by 'compose' with 'pack',
// but this is the basis together with 'fuse'.


#include <boost/mpl/apply.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include "../apply_decl.hpp"
#include "../config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "./use_nullary_result.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Base, class Pack>
    struct nullary_result_of_fused :
        result_of<
            Base const(typename result_of<Pack()>::type)
        >
    { };


    // If 'NullaryResult' is 'boost::use_default', this is not nullary-callable.
    // Else if 'NullaryResult' is 'use_nullary_result', 'Base' is considered
    // as callable with an empty tuple, then the result is inspected.
    // Otherwise, a passed type is the result type of this.

    template<class Base, class NullaryResult, class Pack>
    struct little_unfuse_result
    {
        Base m_base;

        Base const &base() const
        {
            return m_base;
        }

    // 0ary
        typedef typename
            eval_if_use_nullary_result< NullaryResult,
                nullary_result_of_fused<Base, Pack>
            >::type
        nullary_result_type;

        template<class Re>
        Re call() const
        {
            return m_base(Pack()());
        }

    // 1ary-
        template<class Me, PSTADE_EGG_APPLY_DECL_PARAMS(PSTADE_EGG_MAX_LINEAR_ARITY, A)>
        struct PSTADE_EGG_APPLY_DECL;

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/detail/little_unfuse_result.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } } // namespace pstade::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Me, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Me, BOOST_PP_ENUM_PARAMS(n, A)> :
        result_of<
            Base const(typename result_of<Pack(PSTADE_PP_ENUM_PARAMS_WITH(n, A, &))>::type)
        >
    { };

    template<class Re, BOOST_PP_ENUM_PARAMS(n, class A)>
    Re call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, &a)) const
    {
        return m_base(Pack()(BOOST_PP_ENUM_PARAMS(n, a)));
    }


#undef  n
#endif
