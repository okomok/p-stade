#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_CALL_LITTLE_HPP
#define PSTADE_EGG_DETAIL_CALL_LITTLE_HPP
#include "./prefix.hpp"


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
#include <boost/type_traits/remove_cv.hpp>
#include "../config.hpp" // PSTADE_EGG_MAX_LINEAR_ARITY
#include "./call_little_impl.hpp"


namespace pstade { namespace egg {


    #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, PSTADE_EGG_MAX_LINEAR_ARITY, <pstade/egg/detail/call_little.hpp>))
    #include BOOST_PP_ITERATE()


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Re, class Little BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)> inline
    Re call_little(Little& little BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(n, A, & a))
    {
        return call_little_impl<
            typename boost::remove_cv<Little>::type, Re
        >::BOOST_PP_CAT(call, n)(little BOOST_PP_ENUM_TRAILING_PARAMS(n, a));
    }


#undef  n
#endif
