#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_BY_VALUE_HPP
#define PSTADE_EGG_BY_VALUE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// A "movable type" like 'auto_ptr' must be called by value.
// "./by_perfect.hpp" makes rvalue unmovable.


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include "./config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "./detail/apply_little_n.hpp"
#include "./detail/call_little_impl.hpp"
#include "./detail/function_preamble.hpp"
#include "./detail/pp_enum_template_params.hpp"
#include "./function_fwd.hpp"


namespace pstade { namespace egg {


    template<class Little>
    struct function<Little, by_value>
    {
        #include PSTADE_EGG_FUNCTION_PREAMBLE()

        Little m_little;

        Little const& little() const
        {
            return m_little;
        }

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/by_value.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } // namespace pstade::egg


#include "./detail/suffix.hpp"
#endif
#else
#define n BOOST_PP_ITERATION()


    PSTADE_EGG_PP_ENUM_TEMPLATE_PARAMS(n, class A)
    typename BOOST_PP_CAT(apply_little, n)<Little const BOOST_PP_ENUM_TRAILING_PARAMS(n, A)>::type
    operator()(BOOST_PP_ENUM_BINARY_PARAMS(n, A, a)) const
    {
        return call_little_impl<
            Little, typename BOOST_PP_CAT(apply_little, n)<Little const BOOST_PP_ENUM_TRAILING_PARAMS(n, A)>::type
        >::BOOST_PP_CAT(call, n)(m_little BOOST_PP_ENUM_TRAILING_PARAMS(n, a));
    }


#undef  n
#endif
