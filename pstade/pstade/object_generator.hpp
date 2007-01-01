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
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/affect.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/unparenthesize.hpp>


namespace pstade {


    struct object_generator_error_argument_required;


    template<
        class A, class Deducer,
        class Default = object_generator_error_argument_required
    >
    struct deduce :
        boost::mpl::eval_if< boost::is_same<A, void>,
            boost::mpl::identity<Default>,
            boost::mpl::apply1<Deducer, A>
        >
    { };


    namespace deducers {


        struct to_value
        {
            template< class A >
            struct apply :
                pass_by_value<A>
            { };
        };


        struct to_reference
        {
            template< class A >
            struct apply :
                boost::add_reference<A>
            { };
        };


        struct to_qualified
        {
            template< class A >
            struct apply :
                boost::mpl::identity<A>
            { };
        };


    } // namespace deducers


    namespace object_generator_detail {


        template<
            class Lambda,
            BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(PSTADE_CALLABLE_MAX_ARITY, class A, void)
        >
        struct meta_make
        {
            typedef typename
                boost::mpl::BOOST_PP_CAT(apply, PSTADE_CALLABLE_MAX_ARITY)<
                    typename boost::remove_cv<Lambda>::type,
                    BOOST_PP_ENUM_PARAMS(PSTADE_CALLABLE_MAX_ARITY, A)
                >::type
            object_t;

            typedef typename
                affect<Lambda, object_t>::type
            type;
        };


    } // namespace object_generator_detail


    // Boost.MPL seems to fail if 'X<unspecified> x;' is ill-formed
    // even if 'X<unspecified>' is well-formed. So 'NullaryResult' is required.


    template< class Lambda, class NullaryResult = boost::use_default >
    struct object_generator :
        callable< object_generator<Lambda, NullaryResult>, NullaryResult > 
    {

        template< class Myself, PSTADE_CALLABLE_APPLY_PARAMS(A) >
        struct apply
        { };


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
            object_generator_detail::meta_make< Lambda,
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

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_CALLABLE_MAX_ARITY, <pstade/object_generator.hpp>))
        #include BOOST_PP_ITERATE()


    }; // object_generator


    #define PSTADE_OBJECT_GENERATOR(G, Lambda) \
        namespace BOOST_PP_CAT(pstade_object_generator_workarea_, G) { \
            using ::pstade::deduce; \
            using ::pstade::deducers::to_value; \
            using ::pstade::deducers::to_reference; \
            using ::pstade::deducers::to_qualified; \
            using ::boost::mpl::_1; \
            using ::boost::mpl::_2; \
            using ::boost::mpl::_3; \
            using ::boost::mpl::_4; \
            using ::boost::mpl::_5; \
            \
            typedef ::pstade::object_generator< PSTADE_UNPARENTHESIZE(Lambda) > BOOST_PP_CAT(op_, G); \
        } \
        \
        typedef BOOST_PP_CAT(pstade_object_generator_workarea_, G)::BOOST_PP_CAT(op_, G) BOOST_PP_CAT(op_, G); \
        PSTADE_CONSTANT( G, (BOOST_PP_CAT(op_, G)) ) \
    /**/


    // eats unused arguments passed to constructor.
    struct used_only_to_deduce
    {
        template< class T >
        used_only_to_deduce(T const&)
        { }
    };


} // namespace pstade


PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE((pstade)(object_generator), 2)


#endif
#else
#define n BOOST_PP_ITERATION()


template< class Myself, BOOST_PP_ENUM_PARAMS(n, class A) >
struct apply< Myself, BOOST_PP_ENUM_PARAMS(n, A) > :
    object_generator_detail::meta_make< Lambda,
        BOOST_PP_ENUM_PARAMS(n, A)
    >
{ };

template< class Result, BOOST_PP_ENUM_PARAMS(n, class A) >
Result call( PSTADE_PP_ENUM_REF_PARAMS(n, A, a) ) const
{
    return Result(
        BOOST_PP_ENUM_PARAMS(n, a)
    );
}


#undef n
#endif
