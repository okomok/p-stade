#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_BY_PERFECT_HPP
#define PSTADE_EGG_BY_PERFECT_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include "./by_perfect/template.hpp"
#include "./config.hpp" // PSTADE_EGG_MAX_ARITY
#include "./detail/nullary_result.hpp"
#include "./function_fwd.hpp"
#include "./sig_template.hpp"


namespace pstade { namespace egg {


    template<class Baby>
    struct function<Baby, by_perfect>
    {
        typedef function function_type;
        typedef Baby baby_type;

        Baby m_baby;

        Baby baby() const
        {
            return m_baby;
        }

    // 0ary
        typedef typename
            detail::nullary_result<Baby, function>::type
        nullary_result_type;

        nullary_result_type operator()() const
        {
            return detail::call_baby<
                Baby, nullary_result_type
            >::call(m_baby);
        }

    // 1ary-
        template<class FunCall>
        struct result;

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_ARITY, <pstade/egg/by_perfect.hpp>))
        #include BOOST_PP_ITERATE()

        #include PSTADE_EGG_SIG_TEMPLATE()
    };


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    #define  PSTADE_EGG_BY_PERFECT_TEMPLATE_ARITY n
    #include PSTADE_EGG_BY_PERFECT_TEMPLATE()


#undef n
#endif
