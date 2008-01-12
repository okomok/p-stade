#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_UNUSED_HPP
#define PSTADE_UNUSED_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/egg/pstade/pod_constant.hpp>
#include <boost/egg/pstade/preprocessor.hpp>


#if !defined(PSTADE_UNUSED_MAX_ARITY)
    #define PSTADE_UNUSED_MAX_ARITY 20
#endif


namespace pstade {


    struct T_unused
    {
        typedef void result_type;

        // 0ary
        void operator()() const
        { }

        // 1ary
        template< class A0 >
        void operator()(A0 const&) const
        { }

        // 2ary-
        #define BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_UNUSED_MAX_ARITY, <boost/egg/pstade/unused.hpp>))
        #include BOOST_PP_ITERATE()
    };


    PSTADE_POD_CONSTANT((T_unused), unused) = {};


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


template<BOOST_PP_ENUM_PARAMS(n, class A)>
void operator()(PSTADE_PP_ENUM_PARAMS_WITH(n, A, const&)) const
{ }


#undef n
#endif
