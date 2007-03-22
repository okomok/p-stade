#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_FUNCTION_HPP
#define PSTADE_FUNCTION_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of: <boost/detail/function1.hpp>
//
// Copyright David Abrahams 2006. Distributed under the Boost 
// Software License, Version 1.0. (See accompanying 
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) 


// Note:
//
// 'callable' is more generic than this whose 'Baby' can't
// have members, but the definition of 'Baby' can be simpler.
//
// Now 'NullaryResult' must be passed explicitly.
// Something like 'has_nullary_result' would instantiate
// the invalid type with placeholders.
//
// As the result of overload resolution and 'mpl::apply',
// the both const-qualified and non-const-qualified argument type are
// always passed to Baby, and then the Baby is *instantiated*;
// even if the either is never called.
// This might be avoided by using 'template_arguments', though.


#include <boost/mpl/apply.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <pstade/as_mpl_lambda.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>


namespace pstade {


    template<class Baby, class NullaryResult = boost::use_default>
    struct function :
        callable<function<Baby, NullaryResult>, NullaryResult>
    {
        template<class Myself, PSTADE_CALLABLE_APPLY_PARAMS(A)>
        struct apply
        { }; // complete for SFINAE.

        // 0ary
        template<class Result>
        Result call() const
        {
            return Baby()();
        }

        // 1ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_CALLABLE_MAX_ARITY, <pstade/function.hpp>))
        #include BOOST_PP_ITERATE()
    };


    #define PSTADE_FUNCTION(Object, Baby) \
        namespace BOOST_PP_CAT(pstade_function_workarea_of_, Object) { \
            using ::boost::mpl::_; \
            typedef ::pstade::function<PSTADE_AS_MPL_LAMBDA(Baby)> op; \
        } \
        typedef BOOST_PP_CAT(pstade_function_workarea_of_, Object)::op BOOST_PP_CAT(op_, Object); \
        PSTADE_CONSTANT(Object, (BOOST_PP_CAT(op_, Object))) \
    /**/


} // namespace pstade


PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE(pstade::function, 2)


#endif
#else
#define n BOOST_PP_ITERATION()


template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)>
{
    typedef typename boost::mpl::BOOST_PP_CAT(apply, n)<Baby, BOOST_PP_ENUM_PARAMS(n, A)>::type baby_t;
    typedef typename baby_t::result_type type;
};

template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
{
    typedef typename boost::mpl::BOOST_PP_CAT(apply, n)<Baby, BOOST_PP_ENUM_PARAMS(n, A)>::type baby_t;
    return baby_t()(BOOST_PP_ENUM_PARAMS(n, a));
}


#undef n
#endif
