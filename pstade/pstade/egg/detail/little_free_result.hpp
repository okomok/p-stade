#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_LITTLE_FREE_RESULT_HPP
#define PSTADE_EGG_DETAIL_LITTLE_FREE_RESULT_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/is_convertible.hpp>
#include "../apply_decl.hpp"
#include "../config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "../forward.hpp"
#include "./get_pointer_preamble.hpp"
#include "./mem_fun_ptr_traits.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class MemFunPtr, class Strategy>
    struct little_free_result
    {
        typedef typename mem_fun_ptr_traits<MemFunPtr>::class_type class_t;

        MemFunPtr m_ptr;

        template<class Myself, PSTADE_EGG_APPLY_DECL_PARAMS(PSTADE_EGG_MAX_LINEAR_ARITY, A)>
        struct apply
        {
            typedef typename mem_fun_ptr_traits<MemFunPtr>::result_type type;
        };

    #define PSTADE_max_arity BOOST_PP_DEC(PSTADE_EGG_MAX_LINEAR_ARITY)
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, PSTADE_max_arity, <pstade/egg/detail/little_free_result.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_max_arity
    };


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Result, class O BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)>
    Result call(O& o BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(n, A, & a),
        typename enable_if< is_convertible<O*, class_t const*> >::type = 0) const
    {
        return (o.*m_ptr)(PSTADE_EGG_FORWARDING_ARGS(n, a, Strategy const));
    }

    template<class Result, class O BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)>
    Result call(O& o BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(n, A, & a),
        typename disable_if<is_convertible<O*, class_t const*> >::type = 0) const
    {
        PSTADE_EGG_GET_POINTER_PREAMBLE()
        return (get_pointer(o)->*m_ptr)(PSTADE_EGG_FORWARDING_ARGS(n, a, Strategy const));
    }


#undef  n
#endif
