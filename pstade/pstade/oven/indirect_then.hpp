#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_OVEN_INDIRECT_THEN_HPP
#define PSTADE_OVEN_INDIRECT_THEN_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/pointee.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/const_fun.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/preprocessor.hpp>


namespace pstade { namespace oven {


namespace indirect_then_detail {


    template< class Function >
    struct return_op :
        callable< return_op<Function> >
    {
        template< class Myself, PSTADE_CALLABLE_APPLY_PARAMS(A) >
        struct apply
        { };

        // 1ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_CALLABLE_MAX_ARITY, <pstade/oven/indirect_then.hpp>))
        #include BOOST_PP_ITERATE()

        explicit return_op(Function fun) :
            m_fun(fun)
        { }

    private:
        Function m_fun;
    };


} // namespace indirect_then_detail


PSTADE_OBJECT_GENERATOR(indirect_then, (indirect_then_detail::return_op< deduce<_1, as_value> >))


} } // namespace pstade::oven


#endif
#else
#define n BOOST_PP_ITERATION()


template< class Myself, BOOST_PP_ENUM_PARAMS(n, class A) >
struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
    boost::result_of<
        PSTADE_CONST_FUN_TPL(Function)(
            PSTADE_PP_ENUM_PARAMS_WITH(n, typename boost::pointee<typename pass_by_value<A, >::type>::type)
        )
    >
{ };

template< class Result, BOOST_PP_ENUM_PARAMS(n, class A) >
Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
{
    return m_fun(BOOST_PP_ENUM_PARAMS(n, *a));
}


#undef n
#endif
