#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_USE_DEDUCED_FORM_HPP
#define PSTADE_EGG_USE_DEDUCED_FORM_HPP
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
#include <boost/type.hpp> // inclusion guaranteed
#include <pstade/enable_if.hpp>
#include <pstade/has_xxx.hpp>
#include "./config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "./detail/call_little_impl_fwd.hpp"
#include "./detail/pp_enum_template_params.hpp"


namespace pstade { namespace egg {


    PSTADE_HAS_TYPE(use_deduced_form)


    template<class Little, class Re>
    struct call_little_impl<Little, Re,
        typename enable_if< has_use_deduced_form<Little> >::type>
    {
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/use_deduced_form.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } // namespace pstade::egg


#include "./detail/suffix.hpp"
#endif
#else
#define n BOOST_PP_ITERATION()


    PSTADE_EGG_PP_ENUM_TEMPLATE_PARAMS(n, class A)
    static Re BOOST_PP_CAT(call, n)(Little& little BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(n, A, & a))
    {
        return little.call(boost::type<Re>() BOOST_PP_ENUM_TRAILING_PARAMS(n, a));
    }


#undef  n
#endif
