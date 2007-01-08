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
#include <boost/mpl/bool.hpp>
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
#include <pstade/alternative.hpp>
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
            template<class A>
            struct apply :
                pass_by_value<A>
            { };
        };


        struct to_reference
        {
            template<class A>
            struct apply :
                boost::add_reference<A>
            { };
        };


        struct to_qualified
        {
            template<class A>
            struct apply :
                boost::mpl::identity<A>
            { };
        };


    } // namespace deducers


    template<class F>
    struct object_generator_class
    {
        typedef F type;
    };


    namespace object_generator_detail {


        template<class Lambda>
        struct is_object_generator_class :
            boost::mpl::false_
        { };

        template<class F>
        struct is_object_generator_class< object_generator_class<F> > :
            boost::mpl::true_
        { };


        template<class Lambda>
        struct wrap :
            boost::mpl::eval_if< is_object_generator_class<Lambda>,
                Lambda,
                alternative<Lambda>
            >
        { };

        template<class Wrapped, class Lambda>
        struct unwrap :
            boost::mpl::eval_if< is_object_generator_class<Lambda>,
                boost::mpl::identity<Wrapped>,
                alternative_affect<Wrapped, Lambda>
            >
        { };


        template<
            class Lambda,
            BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(PSTADE_CALLABLE_MAX_ARITY, class A, void)
        >
        struct meta_make
        {
            typedef typename
                boost::remove_cv<Lambda>::type // MPL needs this.
            lambda_t;

            typedef typename
                boost::mpl::BOOST_PP_CAT(apply, PSTADE_CALLABLE_MAX_ARITY)<
                    typename wrap<lambda_t>::type,
                    BOOST_PP_ENUM_PARAMS(PSTADE_CALLABLE_MAX_ARITY, A)
                >::type
            wrapped_object_t;

            typedef typename
                affect<Lambda, typename unwrap<wrapped_object_t, lambda_t>::type>::type
            type;
        };


    } // namespace object_generator_detail


    template<
        class Lambda
    >
    struct object_generator :
        callable<
            object_generator<Lambda>,
            typename object_generator_detail::meta_make<Lambda>::type
        > 
    {
        template<class Myself, PSTADE_CALLABLE_APPLY_PARAMS(A)>
        struct apply
        { };

        // 0ary
        template<class Result>
        Result call() const
        {
            return Result();
        }

        // 1ary-
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_CALLABLE_MAX_ARITY, <pstade/object_generator.hpp>))
        #include BOOST_PP_ITERATE()
    };


    #define PSTADE_OBJECT_GENERATOR(G, Lambda) \
        namespace BOOST_PP_CAT(pstade_object_generator_workarea_of_, G) { \
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
            typedef ::pstade::object_generator<PSTADE_UNPARENTHESIZE(Lambda)> op; \
        } \
        \
        typedef BOOST_PP_CAT(pstade_object_generator_workarea_of_, G)::op BOOST_PP_CAT(op_, G); \
        PSTADE_CONSTANT(G, (BOOST_PP_CAT(op_, G))) \
    /**/


    // eats unused arguments passed to constructor.
    struct used_only_to_deduce
    {
        template< class T >
        used_only_to_deduce(T const&)
        { }
    };


} // namespace pstade


PSTADE_CALLABLE_NULLARY_RESULT_OF_TEMPLATE((pstade)(object_generator), 1)


#endif
#else
#define n BOOST_PP_ITERATION()


template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
    object_generator_detail::meta_make<
        Lambda,
        BOOST_PP_ENUM_PARAMS(n, A)
    >
{ };

template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
Result call(PSTADE_PP_ENUM_REF_PARAMS(n, A, a)) const
{
    return Result(
        BOOST_PP_ENUM_PARAMS(n, a)
    );
}


#undef n
#endif
