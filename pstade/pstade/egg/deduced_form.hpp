#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DEDUCED_FORM_HPP
#define PSTADE_EGG_DEDUCED_FORM_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type.hpp>
#include <pstade/enable_if.hpp>
#include "./config.hpp"
#include "./detail/is_calling_strategy_of.hpp"
#include "./detail/call_baby_fwd.hpp"


namespace pstade { namespace egg {
    

    struct deduced_form;


    namespace detail {


        template<class Result> inline
        boost::type<Result> deduced_()
        {
            return boost::type<Result>();
        }


        template<class Baby_, class Result>
        struct call_baby<Baby_, Result,
            typename enable_if< is_calling_strategy_of<deduced_form, Baby_> >::type >
        {
        // 0ary
            template<class Baby>
            static Result call(Baby& baby)
            {
                return baby.call(deduced_<Result>());
            }

        // 1ary-
            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/deduced_form.hpp>))
            #include BOOST_PP_ITERATE()
        };


    } // namespace detail


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Baby, BOOST_PP_ENUM_PARAMS(n, class A)>
    static Result call(Baby& baby, BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a))
    {
        return baby.call(deduced_<Result>(), BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef n
#endif
