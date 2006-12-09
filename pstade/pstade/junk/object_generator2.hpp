#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_OBJECT_GENERATOR_HPP
#define PSTADE_OBJECT_GENERATOR_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/preprocessor.hpp>


namespace pstade {


    struct object_by_value;
    struct object_by_qualifier;
    struct object_by_reference;


    namespace object_generator_detail {


        template< class Affect, class A >
        struct template_argument :
            boost::mpl::eval_if< boost::is_same< object_by_value, Affect >,
                pass_by_value<A>,
                boost::mpl::eval_if< boost::is_same< object_by_reference, Affect >,
                    boost::add_reference<A>,
                    boost::mpl::identity<A>
                >
            >
        { };


    } // namespace object_generator_detail


    // To: MPL LambdaExpression.

    template< class To,
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(PSTADE_CALLABLE_MAX_ARITY, class Affect, object_by_value)
    >
    struct object_generator :
        callable<
            object_generator< To,
                BOOST_PP_ENUM_PARAMS(PSTADE_CALLABLE_MAX_ARITY, Affect)
            >
        >
    {

    #define PSTADE_template_argument(Z, N, _) \
        typename object_generator_detail::template_argument<BOOST_PP_CAT(Affect, N), BOOST_PP_CAT(A, N)>::type \
    /**/

        // PSTADE_CALLABLE_MAX_ARITY (primary)

        template< class Myself, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(PSTADE_CALLABLE_MAX_ARITY, class A, void) >
        struct apply
        {
            typedef typename
                boost::mpl::BOOST_PP_CAT(apply, PSTADE_CALLABLE_MAX_ARITY)< To,
                    BOOST_PP_ENUM(PSTADE_CALLABLE_MAX_ARITY, PSTADE_template_argument, ~)
                >::type const
            type;
        };

        template< class Result, BOOST_PP_ENUM_PARAMS(PSTADE_CALLABLE_MAX_ARITY, class A) >
        Result call( PSTADE_PP_ENUM_REF_PARAMS_WITH_OBJECTS(PSTADE_CALLABLE_MAX_ARITY, A, a) ) const
        {
            return Result( BOOST_PP_ENUM_PARAMS(PSTADE_CALLABLE_MAX_ARITY, a) );
        }


        // 1ary

        template< class Myself, class A0 >
        struct apply<Myself, A0>
        {
            typedef typename
                boost::mpl::apply1< To,
                    typename object_generator_detail::template_argument<Affect0, A0>::type
                >::type const
            type;
        };

        template< class Result, class A0 >
        Result call(A0& a0) const
        {
            return Result( a0 );
        }
                

        // 2ary -

    #define PSTADE_max_arity BOOST_PP_DEC(PSTADE_CALLABLE_MAX_ARITY)
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_max_arity, <pstade/object_generator.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_max_arity
    
    #undef  PSTADE_template_argument


    }; // object_generator


    typedef boost::mpl::placeholders::_1 object_1;
    typedef boost::mpl::placeholders::_2 object_2;
    typedef boost::mpl::placeholders::_3 object_3;
    typedef boost::mpl::placeholders::_4 object_4;
    typedef boost::mpl::placeholders::_5 object_5;


    // Prefer the followings to PlaceholderExpression if...
    // 1. The type is not DefaultConstructible;
    //    GCC3.4 complains "with only non-default constructor in class without a constructor".
    // 2. A nested 'type' is different from what you want to generate.
    // 3. You want to ignore redundant arguments passed.

    template< template< class > class T >
    struct object_of1
    {
        template< class A0, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(4, class X, void) >
        struct apply
        {
            typedef T<A0> type;
        };
    };

    template< template< class, class > class T >
    struct object_of2
    {
        template< class A0, class A1, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(3, class X, void) >
        struct apply
        {
            typedef T<A0, A1> type;
        };
    };

    template< template< class, class, class > class T >
    struct object_of3
    {
        template< class A0, class A1, class A2, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(2, class X, void) >
        struct apply
        {
            typedef T<A0, A1, A2> type;
        };
    };

    template< template< class, class, class, class > class T >
    struct object_of4
    {
        template< class A0, class A1, class A2, class A3, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(1, class X, void) >
        struct apply
        {
            typedef T<A0, A1, A2, A3> type;
        };
    };

    template< template< class, class, class, class, class > class T >
    struct object_of5
    {
        template< class A0, class A1, class A2, class A3, class A4 >
        struct apply
        {
            typedef T<A0, A1, A2, A3, A4> type;
        };
    };


    #define PSTADE_OBJECT_GENERATOR(G, T, N, AffectSeq) \
        typedef \
            pstade::object_generator<pstade::BOOST_PP_CAT(object_of, N)< T >, BOOST_PP_SEQ_ENUM(AffectSeq)> \
        BOOST_PP_CAT(op_, G); \
        \
        PSTADE_CONSTANT(G, BOOST_PP_CAT(op_, G)) \
    /**/


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


template< class Myself, BOOST_PP_ENUM_PARAMS(n, class A) >
struct apply< Myself, BOOST_PP_ENUM_PARAMS(n, A) >
{
    typedef typename
        boost::mpl::BOOST_PP_CAT(apply, n)< To,
            BOOST_PP_ENUM(n, PSTADE_template_argument, ~)
        >::type const
    type;
};

template< class Result, BOOST_PP_ENUM_PARAMS(n, class A) >
Result call( PSTADE_PP_ENUM_REF_PARAMS_WITH_OBJECTS(n, A, a) ) const
{
    return Result( BOOST_PP_ENUM_PARAMS(n, a) );
}


#undef n
#endif
