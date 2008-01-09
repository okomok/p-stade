#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DEDUCED_FORM_HPP
#define PSTADE_EGG_DEDUCED_FORM_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/type.hpp>
#include <pstade/enable_if.hpp>
#include "./config.hpp"
#include "./detail/call_little_impl_fwd.hpp"
#include "./detail/is_call_strategy_of.hpp"


namespace pstade { namespace egg {


    struct deduced_form;


    namespace detail {


        template<class Little_, class Result>
        struct call_little_impl<Little_, Result,
            typename enable_if< is_call_strategy_of<deduced_form, Little_> >::type >
        {
            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/deduced_form.hpp>))
            #include BOOST_PP_ITERATE()
        };


    } // namespace detail


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Little BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)>
    static Result BOOST_PP_CAT(call, n)(Little& little BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(n, A, & a))
    {
        return little.call(boost::type<Result>() BOOST_PP_ENUM_TRAILING_PARAMS(n, a));
    }


#undef n
#endif
