#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_OBJECT_GENERATOR_HPP
#define PSTADE_EGG_OBJECT_GENERATOR_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/type.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/affect.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/unparenthesize.hpp>
#include <pstade/use_default.hpp>
#include "./apply_params.hpp"
#include "./callable.hpp"
#include "./detail/config.hpp" // PSTADE_EGG_MAX_ARITY
#include "./detail/non_aggregate.hpp"
#include "./detail/template_arguments.hpp"


namespace pstade { namespace egg {


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


        struct as_value
        {
            template<class A>
            struct apply :
                pass_by_value<A>
            { };
        };


        struct as_reference
        {
            template<class A>
            struct apply :
                boost::add_reference<A>
            { };
        };


        struct as_qualified
        {
            template<class A>
            struct apply :
                boost::mpl::identity<A>
            { };
        };


    } // namespace deducers


    namespace object_generator_detail {


        template<class Lambda>
        struct is_placeholder_expression :
            boost::mpl::is_lambda_expression<Lambda>
        { };


        // Work around "ETI" of 'boost::mpl::apply'.

        template<class Lambda>
        struct to_alternative :
            boost::mpl::eval_if< is_placeholder_expression<Lambda>,
                detail::template_arguments_of<Lambda>,
                boost::mpl::identity<Lambda>
            >
        { };

        template<class Alternative, class Lambda>
        struct alternative_to :
            boost::mpl::eval_if< is_placeholder_expression<Lambda>,
                detail::template_arguments_copy<Alternative, Lambda>,
                boost::mpl::identity<Alternative>
            >
        { };


        template<
            class Lambda,
            PSTADE_PP_ENUM_PARAMS_WITH(PSTADE_EGG_MAX_ARITY, class A, = void)
        >
        struct object_of
        {
            typedef typename
                boost::remove_cv<Lambda>::type // MPL needs this.
            lambda_t;

            typedef typename
                boost::mpl::BOOST_PP_CAT(apply, PSTADE_EGG_MAX_ARITY)<
                    typename to_alternative<lambda_t>::type,
                    BOOST_PP_ENUM_PARAMS(PSTADE_EGG_MAX_ARITY, A)
                >::type
            alt_object_t;

            typedef typename
                affect<Lambda, typename alternative_to<alt_object_t, lambda_t>::type>::type
            type;
        };


        template<class Lambda, class What>
        struct baby
        {
            template<class Myself, PSTADE_EGG_APPLY_PARAMS(A)>
            struct apply
            { };

            // 0ary
            template<class Result>
            Result call() const
            {
                return Result();
            }

            // 1ary-
            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_ARITY, <pstade/egg/object_generator.hpp>))
            #include BOOST_PP_ITERATE()
        };


    } // namespace object_generator_detail


    // Even if using 'to_alternative', 'NullaryResult' must be explicitly specified.
    // E.g. 'my< some_metafunction<_1> >' where 'some_metafunction<void>::type' is ill-formed.

    template<class Lambda, class What = boost::use_default, class NullaryResult = boost::use_default>
    struct object_generator
    {
        typedef typename if_use_default<What, detail::non_aggregate>::type make_t;
        typedef callable<object_generator_detail::baby<Lambda, make_t>, NullaryResult> type;
    };


    namespace object_generator_helpers {
        using pstade::egg::deduce;
        using namespace pstade::egg::deducers;
        using namespace boost::mpl::placeholders;
    }


    #define PSTADE_EGG_OBJECT_GENERATOR(G, L) \
        namespace BOOST_PP_CAT(pstade_egg_object_generator_workarea_of_, G) { \
            using namespace pstade::egg::object_generator_helpers; \
            typedef pstade::egg::object_generator<PSTADE_UNPARENTHESIZE(L)>::type op; \
        } \
        typedef BOOST_PP_CAT(pstade_egg_object_generator_workarea_of_, G)::op BOOST_PP_CAT(op_, G); \
        PSTADE_POD_CONSTANT(G, (BOOST_PP_CAT(op_, G))) \
    /**/


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)> :
        object_of<
            Lambda, BOOST_PP_ENUM_PARAMS(n, A)
        >
    { };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        return What()(boost::type<Result>(), BOOST_PP_ENUM_PARAMS(n, a));
    }


#undef n
#endif
