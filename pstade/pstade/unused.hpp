#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_UNUSED_HPP
#define PSTADE_UNUSED_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/constant.hpp>
#include <pstade/preprocessor.hpp>


#if !defined(PSTADE_UNUSED_MAX_ARITY)
    #define PSTADE_UNUSED_MAX_ARITY 20
#endif


namespace pstade {


    struct op_unused
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
        #define BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_UNUSED_MAX_ARITY, <pstade/unused.hpp>))
        #include BOOST_PP_ITERATE()
    };


    PSTADE_CONSTANT(unused, (op_unused))


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


template<BOOST_PP_ENUM_PARAMS(n, class A)>
void operator()(PSTADE_PP_ENUM_PARAMS_WITH(n, A, const&)) const
{ }


#undef n
#endif
