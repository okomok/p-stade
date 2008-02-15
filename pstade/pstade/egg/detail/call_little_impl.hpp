#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_CALL_LITTLE_IMPL_HPP
#define PSTADE_EGG_DETAIL_CALL_LITTLE_IMPL_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include "../config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "./call_little_impl_fwd.hpp"
#include "./pp_enum_template_params.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Little, class Re, class EnableIf>
    struct call_little_impl
    {
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/detail/call_little_impl.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    PSTADE_EGG_PP_ENUM_TEMPLATE_PARAMS(n, class A)
    static Re call(Little &little BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(n, A, &a))
    {
        return little.template call<Re>(BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef  n
#endif
