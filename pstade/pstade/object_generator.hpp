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
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/affect.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/remove_cvr.hpp>


namespace pstade {


    typedef boost::mpl::_  from_;
    typedef boost::mpl::_1 from_1;
    typedef boost::mpl::_2 from_2;
    typedef boost::mpl::_3 from_3;
    typedef boost::mpl::_4 from_4;
    typedef boost::mpl::_5 from_5;


    // predefined deducers


    struct argument_not_passed;
    struct object_generator_error_argument_required;


    template<
        class A, class F,
        class Default = object_generator_error_argument_required
    >
    struct deduce_to :
        boost::mpl::eval_if< boost::is_same<A, argument_not_passed>,
            boost::mpl::identity<Default>,
            F
        >
    { };


    template<
        class A,
        class Default = object_generator_error_argument_required
    >
    struct deduce_to_value :
        deduce_to<
            A, pass_by_value<A>,
            Default
        >
    { };

    template<
        class A,
        class Default = object_generator_error_argument_required
    >
    struct deduce_to_reference :
        deduce_to<
            A, boost::add_reference<A>,
            Default
        >
    { };

    template<
        class A,
        class Default = object_generator_error_argument_required
    >
    struct deduce_to_qualified :
        deduce_to<
            A, boost::mpl::identity<A>,
            Default
        >
    { };


    // utility


    struct unused_argument
    {
        unused_argument()
        { }

        template< class T >
        unused_argument(T const&)
        { }
    };


    // the object_generator


    namespace object_generator_detail {


        template<
            class Lambda,
            BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(PSTADE_CALLABLE_MAX_ARITY, class A, argument_not_passed)
        >
        struct make
        {
            typedef typename
                boost::mpl::BOOST_PP_CAT(apply, PSTADE_CALLABLE_MAX_ARITY)<
                    typename remove_cvr<Lambda>::type,
                    BOOST_PP_ENUM_PARAMS(PSTADE_CALLABLE_MAX_ARITY, A)
                >::type
            object_t;

            typedef typename
                affect_cvr<Lambda, object_t>::type
            type;
        };


    } // namespace object_generator_detail


    // Boost.MPL seems to fail if 'X<unspecified> x;' is ill-formed
    // even if 'X<unspecified>' is well-formed. So 'NullaryResult' is required.


    template< class Lambda, class NullaryResult = void >
    struct object_generator :
        callable< object_generator<Lambda, NullaryResult>, NullaryResult > 
    {

        // PSTADE_CALLABLE_MAX_ARITY (primary)

        template< class Myself, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(PSTADE_CALLABLE_MAX_ARITY, class A, void) >
        struct apply :
            object_generator_detail::make< Lambda,
                BOOST_PP_ENUM_PARAMS(PSTADE_CALLABLE_MAX_ARITY, A)
            >
        { };

        template< class Result, BOOST_PP_ENUM_PARAMS(PSTADE_CALLABLE_MAX_ARITY, class A) >
        Result call( PSTADE_PP_ENUM_REF_PARAMS_WITH_OBJECTS(PSTADE_CALLABLE_MAX_ARITY, A, a) ) const
        {
            return Result(
                BOOST_PP_ENUM_PARAMS(PSTADE_CALLABLE_MAX_ARITY, a)
            );
        }


        // 0ary

        template< class Result >
        Result call( ) const
        {
            return Result(
            );
        }


        // 1ary

        template< class Myself, class A0 >
        struct apply< Myself, A0 > :
            object_generator_detail::make< Lambda,
                A0
            >
        { };

        template< class Result, class A0 >
        Result call( A0& a0 ) const
        {
            return Result(
                a0
            );
        }
                

        // 2ary-

    #define PSTADE_max_arity BOOST_PP_DEC(PSTADE_CALLABLE_MAX_ARITY)
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_max_arity, <pstade/object_generator.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_max_arity


    }; // object_generator


    #define PSTADE_OBJECT_GENERATOR(G, Lambda) \
        typedef pstade::object_generator< Lambda > BOOST_PP_CAT(op_, G); \
        PSTADE_CONSTANT(G, BOOST_PP_CAT(op_, G)) \
    /**/


} // namespace pstade


PSTADE_CALLABLE_NULLARY_RESULT_TEMPLATE((pstade)(object_generator), 2)


#endif
#else
#define n BOOST_PP_ITERATION()


template< class Myself, BOOST_PP_ENUM_PARAMS(n, class A) >
struct apply< Myself, BOOST_PP_ENUM_PARAMS(n, A) > :
    object_generator_detail::make< Lambda,
        BOOST_PP_ENUM_PARAMS(n, A)
    >
{ };

template< class Result, BOOST_PP_ENUM_PARAMS(n, class A) >
Result call( PSTADE_PP_ENUM_REF_PARAMS_WITH_OBJECTS(n, A, a) ) const
{
    return Result(
        BOOST_PP_ENUM_PARAMS(n, a)
    );
}


#undef n
#endif
