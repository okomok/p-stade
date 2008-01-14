#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_USE_CONSTRUCTOR_HPP
#define PSTADE_EGG_USE_CONSTRUCTOR_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/limits/arity.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include "./forward.hpp"


namespace pstade { namespace egg {


    struct use_constructor
    {
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (0, BOOST_MPL_LIMIT_METAFUNCTION_ARITY, <pstade/egg/use_constructor.hpp>))
        #include BOOST_PP_ITERATE()
    };


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class X, class Strategy BOOST_PP_ENUM_TRAILING_PARAMS(n, class A)>
    static X BOOST_PP_CAT(call, n)(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a))
    {
        return X(PSTADE_EGG_FORWARDING_ARGS(n, a, Strategy));
    }
    

#undef n
#endif
