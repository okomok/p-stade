#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_FUNCTION_HPP
#define PSTADE_FUNCTION_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// This is virtually a short version of 'forward'.
// Note that 'callable' is more generic than this, but
// it needs NULLARY_RESULT_OF macro; this doesn't.


#include <boost/config.hpp> // BOOST_NESTED_TEMPLATE
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/has_xxx.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/unparenthesize.hpp>


namespace pstade {


    namespace function_detail {


        PSTADE_HAS_TYPE(nullary_result_type)

        template<class Baby>
        struct nullary_result_aux
        {
            typedef typename Baby::nullary_result_type type;
        };

        template<class Baby>
        struct nullary_result :
            boost::mpl::eval_if< has_nullary_result_type<Baby>,
                nullary_result_aux<Baby>,
                boost::mpl::identity<boost::use_default>
            >
        { };


    } // namespace function_detail


    template<class Baby>
    struct function :
        callable<function<Baby>, typename function_detail::nullary_result<Baby>::type>
    {
        template<class Myself, PSTADE_CALLABLE_APPLY_PARAMS(A)>
        struct apply
        { }; // complete for SFINAE.

        // 0ary
        template<class Result>
        Result call() const
        {
            return Baby().BOOST_NESTED_TEMPLATE call<Result>();
        }

        // 1ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_CALLABLE_MAX_ARITY, <pstade/function.hpp>))
        #include BOOST_PP_ITERATE()
    };


    #define PSTADE_FUNCTION(Object, Baby) \
        typedef ::pstade::function<PSTADE_UNPARENTHESIZE(Baby)> BOOST_PP_CAT(op_, Object); \
        PSTADE_CONSTANT( Object, (BOOST_PP_CAT(op_, Object)) ) \
    /**/


} // namespace pstade


PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE((pstade)(function), 1)


#endif
#else
#define n BOOST_PP_ITERATION()


template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
    Baby::BOOST_NESTED_TEMPLATE apply<Baby, BOOST_PP_ENUM_PARAMS(n, A)>
{ };

template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
Result call(PSTADE_PP_ENUM_REF_PARAMS(n, A, a)) const
{
    return Baby().BOOST_NESTED_TEMPLATE call<Result>(BOOST_PP_ENUM_PARAMS(n, a));
}


#undef n
#endif
