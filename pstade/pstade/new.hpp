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
#include <pstade/constant.hpp>
#include <pstade/preprocessor.hpp>


namespace pstade {


    template<class X>
    struct new_ :
        callable<new_<X>, std::auto_ptr<X> >
    {
        PSTADE_CALLABLE_PRIMARY_APPLY
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


} // namespace pstade


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
