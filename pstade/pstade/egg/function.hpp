#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_FUNCTION_HPP
#define PSTADE_FUNCTION_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
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
// 'callable' is more generic than this whose 'Lambda' can't
// have members, but the definition of 'Lambda' can be simpler.
//
// Now 'NullaryResult' must be passed explicitly.
// Something like 'has_nullary_result' would instantiate
// the invalid type with placeholders.
//
// As the result of overload resolution and 'mpl::apply',
// the both const-qualified and non-const-qualified argument type are
// always passed to Lambda, and then the Lambda is *instantiated*;
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
#include "./apply_params.hpp"
#include "./callable.hpp"
#include "./detail/as_mpl_lambda.hpp"
#include "./detail/config.hpp" // PSTADE_EGG_MAX_ARITY
#include "./nullary_result_of.hpp"
#include "./object.hpp"


namespace pstade { namespace egg {


    template<class Lambda, class NullaryResult = boost::use_default>
    struct function :
        callable<function<Lambda, NullaryResult>, NullaryResult>
    {
        template<class Myself, PSTADE_EGG_APPLY_PARAMS(A)>
        struct apply
        { }; // msvc warns if incomplete.

        // 0ary
        template<class Result>
        Result call(boost::type<Result>) const
        {
            return Lambda()();
        }

        // These are redefined in 'apply'.
    #define PSTADE_typedef_default_arg(Z, N, _) typedef boost::mpl::void_ BOOST_PP_CAT(arg, N);
        BOOST_PP_REPEAT(BOOST_MPL_LIMIT_METAFUNCTION_ARITY, PSTADE_typedef_default_arg, ~)
    #undef  PSTADE_typedef_default_arg

        // 1ary-
    #define PSTADE_typedef_arg(Z, N, _) typedef BOOST_PP_CAT(A, N) BOOST_PP_CAT(arg, N);
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_ARITY, <pstade/egg/function.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_typedef_arg
    };


    #define PSTADE_EGG_FUNCTION(O, L) \
        namespace BOOST_PP_CAT(pstade_egg_function_workarea_of_, O) { \
            using namespace ::boost::mpl::placeholders; \
            typedef ::pstade::egg::function<PSTADE_EGG_DETAIL_AS_MPL_LAMBDA(L)> op; \
        } \
        typedef BOOST_PP_CAT(pstade_egg_function_workarea_of_, O)::op BOOST_PP_CAT(op_, O); \
        PSTADE_EGG_OBJECT(O, (BOOST_PP_CAT(op_, O))) \
    /**/


} } // namespace pstade::egg


PSTADE_EGG_NULLARY_RESULT_OF_TEMPLATE(pstade::egg::function, 2)


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)>
    {
        BOOST_PP_REPEAT(n, PSTADE_typedef_arg, ~)

        // fixed number 'apply' for lightweight compiling
        typedef typename
            BOOST_PP_CAT(boost::mpl::apply, BOOST_MPL_LIMIT_METAFUNCTION_ARITY)<
                Lambda, BOOST_PP_ENUM_PARAMS(BOOST_MPL_LIMIT_METAFUNCTION_ARITY, arg)
            >::type
        impl_t;

        typedef typename impl_t::result_type type;
    };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a), boost::type<Result>) const
    {
        typedef typename apply<void, BOOST_PP_ENUM_PARAMS(n, A)>::impl_t impl_t;
        return impl_t()(BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef n
#endif
