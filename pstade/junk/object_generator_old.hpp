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
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/seq/size.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/preprocessor/seq/for_each_i.hpp>
#include <boost/preprocessor/seq/transform.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/use_default.hpp>


namespace pstade {


    struct deduce_to_value;
    struct deduce_to_reference;
    struct deduce_to_qualified;


    namespace object_generator_detail {


        template< class By, class A >
        struct template_argument :
            boost::mpl::eval_if< boost::is_same<By, deduce_to_value>,
                pass_by_value<A>,
                boost::mpl::eval_if< boost::is_same<By, deduce_to_reference>,
                    boost::add_reference<A>,
                    boost::mpl::identity<A>
                >
            >
        { };


    } // namespace object_generator_detail


    template<
        class To,
        class NullaryResult = boost::use_default,
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(PSTADE_CALLABLE_MAX_ARITY, class By, void)
    >
    struct object_generator :
        callable<
            object_generator< To, NullaryResult, BOOST_PP_ENUM_PARAMS(PSTADE_CALLABLE_MAX_ARITY, By) >,
            typename defaultable_eval_to< NullaryResult, boost::mpl::apply0<To> >::type
        >
    {

    #define PSTADE_template_argument(Z, N, _) \
        typename object_generator_detail::template_argument< BOOST_PP_CAT(By, N), BOOST_PP_CAT(A, N) >::type \
    /**/

        // PSTADE_CALLABLE_MAX_ARITY (primary)

        template< class Myself, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(PSTADE_CALLABLE_MAX_ARITY, class A, void) >
        struct apply :
            boost::mpl::BOOST_PP_CAT(apply, PSTADE_CALLABLE_MAX_ARITY)< To,
                BOOST_PP_ENUM(PSTADE_CALLABLE_MAX_ARITY, PSTADE_template_argument, ~)
            >
        { };

        template< class Result, BOOST_PP_ENUM_PARAMS(PSTADE_CALLABLE_MAX_ARITY, class A) >
        Result call( PSTADE_PP_ENUM_REF_PARAMS_WITH_OBJECTS(PSTADE_CALLABLE_MAX_ARITY, A, a) ) const
        {
            return Result( BOOST_PP_ENUM_PARAMS(PSTADE_CALLABLE_MAX_ARITY, a) );
        }


        // 0ary

        template< class Result >
        Result call( ) const
        {
            return Result( );
        }


        // 1ary

        template< class Myself, class A0 >
        struct apply< Myself, A0 > :
            boost::mpl::apply1< To,
                typename object_generator_detail::template_argument<By0, A0>::type
            >
        { };

        template< class Result, class A0 >
        Result call( A0& a0 ) const
        {
            return Result( a0 );
        }
                

        // 2ary-

    #define PSTADE_max_arity BOOST_PP_DEC(PSTADE_CALLABLE_MAX_ARITY)
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_max_arity, <pstade/object_generator.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_max_arity
    
    #undef  PSTADE_template_argument


    }; // object_generator


    // Rationale:
    //
    // The following macro was preferred to PlaceholderExpression because...
    // 1. 'To' must be nullary for the nullary result declaration.
    // 2. GCC3.4 requires Metafunction to be DefaultConstructible. Doh!
    // 3. A PlaceHolderExpression can't ignore redundant arguments.
    // 4. A nested 'type' is sometimes different from what you wanna generate.
    // 5. 'X<mpl::_1>' is not always well-formed.


    struct argument_required;


    #define PSTADE_OBJECT_GENERATOR(G, X, BySeq, DefaultSeq) \
        PSTADE_OBJECT_GENERATOR_aux(G, X, void, BySeq, PSTADE_PP_SEQ_TO_SEQ(DefaultSeq, (pstade::argument_required))) \
    /**/

    #define PSTADE_OBJECT_GENERATOR_NULLARY(G, X, NullaryResult, BySeq, DefaultSeq) \
        PSTADE_OBJECT_GENERATOR_aux(G, X, NullaryResult, BySeq, DefaultSeq, NullaryResult) \
    /**/


    // Requirements:
    //
    // Assume 'N' is the size of 'BySeq', and 'DefaultSeq_' is 'DefaultSeq' ++ 'argument_required_seq'.
    //
    // 1. 'X' is a template, where cv-qualifier may be followed.
    // 2. 'X<DefaultSeq_[0],..,DefaultSeq_[N-1]>' is well-formed if 'NullaryResult' is 'boost::use_default'.


    #define PSTADE_OBJECT_GENERATOR_aux(G, X, NullaryResult, BySeq, DefaultSeq) \
        struct BOOST_PP_CAT(pstade_object_generator_quote_of_, G) \
        { \
            template< BOOST_PP_SEQ_ENUM( \
                BOOST_PP_SEQ_FOR_EACH_I(PSTADE_OBJECT_GENERATOR_with_default, ~, DefaultSeq PSTADE_OBJECT_GENERATOR_argument_required_seq) \
            ) > \
            struct apply \
            { \
                typedef X< BOOST_PP_ENUM_PARAMS(BOOST_PP_SEQ_SIZE(BySeq), A) > type; \
            }; \
        }; \
        \
        typedef pstade::object_generator< \
            BOOST_PP_CAT(pstade_object_generator_quote_of_, G), \
            NullaryResult, \
            BOOST_PP_SEQ_ENUM( BOOST_PP_SEQ_TRANSFORM(PSTADE_OBJECT_GENERATOR_to_fullname, ~, BySeq) ) \
        > BOOST_PP_CAT(op_, G); \
        \
        PSTADE_CONSTANT(G, BOOST_PP_CAT(op_, G)) \
    /**/

        #define PSTADE_OBJECT_GENERATOR_with_default(R, _, I, Elem) \
            (class BOOST_PP_CAT(A, I) = Elem) \
        /**/

        #define PSTADE_OBJECT_GENERATOR_to_fullname(S, _, Elem) \
            pstade:: BOOST_PP_CAT(deduce_, Elem) \
        /**/

        #define PSTADE_OBJECT_GENERATOR_argument_required_seq \
            PSTADE_PP_SEQ_REPLICATE(PSTADE_CALLABLE_MAX_ARITY, pstade::argument_required) \
        /**/


} // namespace pstade


PSTADE_CALLABLE_NULLARY_RESULT_TEMPLATE((pstade)(object_generator), BOOST_PP_ADD(PSTADE_CALLABLE_MAX_ARITY, 2))


#endif
#else
#define n BOOST_PP_ITERATION()


template< class Myself, BOOST_PP_ENUM_PARAMS(n, class A) >
struct apply< Myself, BOOST_PP_ENUM_PARAMS(n, A) > :
    boost::mpl::BOOST_PP_CAT(apply, n)< To,
        BOOST_PP_ENUM(n, PSTADE_template_argument, ~)
    >
{ };

template< class Result, BOOST_PP_ENUM_PARAMS(n, class A) >
Result call( PSTADE_PP_ENUM_REF_PARAMS_WITH_OBJECTS(n, A, a) ) const
{
    return Result( BOOST_PP_ENUM_PARAMS(n, a) );
}


#undef n
#endif
