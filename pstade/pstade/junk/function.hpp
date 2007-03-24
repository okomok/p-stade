#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_FUNCTION_HPP
#define PSTADE_FUNCTION_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of: <boost/detail/function_n.hpp>
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
#include <boost/mpl/void.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <pstade/as_mpl_lambda.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/preprocessor.hpp>


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
    #define PSTADE_typedef_void_arg(Z, N, _) typedef boost::mpl::void_  BOOST_PP_CAT(arg, N);
    #define PSTADE_typedef_A_arg(Z, N, _)    typedef BOOST_PP_CAT(A, N) BOOST_PP_CAT(arg, N);
        BOOST_PP_REPEAT(BOOST_MPL_LIMIT_METAFUNCTION_ARITY, PSTADE_typedef_void_arg, ~)
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_CALLABLE_MAX_ARITY, <pstade/function.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_typedef_A_arg
    #undef  PSTADE_typedef_void_arg
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
    // Use only 'mpl::apply5'; for maybe efficient compilation.
    BOOST_PP_REPEAT(n, PSTADE_typedef_A_arg, ~) // hides outer 'void_' argN.
    typedef typename
        boost::mpl::BOOST_PP_CAT(apply, BOOST_MPL_LIMIT_METAFUNCTION_ARITY)<
            Baby, BOOST_PP_ENUM_PARAMS(BOOST_MPL_LIMIT_METAFUNCTION_ARITY, arg)
        >::type
    baby_t;
    typedef typename baby_t::result_type type;
};

template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
{
    typedef typename apply<void, BOOST_PP_ENUM_PARAMS(n, A)>::baby_t baby_t;
    return baby_t()(BOOST_PP_ENUM_PARAMS(n, a));
}


#undef n
#endif
