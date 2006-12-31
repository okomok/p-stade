#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_NEW_HPP
#define PSTADE_NEW_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <memory> // auto_ptr
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/callable.hpp>
#include <pstade/preprocessor.hpp>


namespace pstade {


    template<class X>
    struct op_new_ :
        callable<op_new_<X>, std::auto_ptr<X> >
    {
        template<class Myself, PSTADE_CALLABLE_APPLY_PARAMS(A)>
        struct apply
        {
            typedef std::auto_ptr<X> type;
        };

        // 0ary
        template<class Result>
        Result call() const
        {
            return Result(new X());
        }

        // workaround for vexing parse
        std::auto_ptr<X> call() const
        {
            return std::auto_ptr<X>(new X());
        }

        // 1ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_CALLABLE_MAX_ARITY, <pstade/new.hpp>))
        #include BOOST_PP_ITERATE()
    };


    // There is no 'new_' yet.
    // Yet another 63 functions seems bad?
    // Also note it is impossible for 'automatic'
    // to work with 'auto_ptr' which is not CopyConstructible.


} // namespace pstade


PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE((pstade)(op_new_), 1)


#endif
#else
#define n BOOST_PP_ITERATION()


template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
Result call(PSTADE_PP_ENUM_REF_PARAMS(n, A, a)) const
{
    return Result(new X(BOOST_PP_ENUM_PARAMS(n, a)));
}


#undef n
#endif
