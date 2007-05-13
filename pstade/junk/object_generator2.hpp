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
#include <boost/mpl/arg.hpp>
#include <boost/mpl/if.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/remove_cvr.hpp>


namespace pstade {


    namespace object_generator_detail {


        struct not_passed;
        

        template< class A, class Default >
        struct default_filter :
            boost::mpl::if_< boost::is_same<typename remove_cvr<A>::type, not_passed>,
                Default,
                A
            >
        { };


    } // namespace object_generator_detail


    struct object_generator_error_argument_required;


    template< int N, class Default = object_generator_error_argument_required >
    struct deduce_to_value
    {
        template< BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(PSTADE_CALLABLE_MAX_ARITY, class A, object_generator_detail::not_passed) >
        struct apply :
            object_generator_detail::default_filter<
                pass_by_value<
                    typename boost::mpl::apply<boost::mpl::arg<N>, A0, A1, A2>::type
                >,
                Default
            >
        { };
    };

    template< int N, class Default = object_generator_error_argument_required >
    struct deduce_to_reference
    {
        template< BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(PSTADE_CALLABLE_MAX_ARITY, class A, object_generator_detail::not_passed) >
        struct apply :
            object_generator_detail::default_filter<
                boost::add_reference<
                    typename boost::mpl::apply<boost::mpl::arg<N>, A0, A1, A2>::type
                >,
                Default
            >
        { };
    };

    template< int N, class Default = object_generator_error_argument_required >
    struct deduce_to_qualified
    {
        template< BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(PSTADE_CALLABLE_MAX_ARITY, class A, object_generator_detail::not_passed) >
        struct apply :
            object_generator_detail::default_filter<
                boost::mpl::apply<boost::mpl::arg<N>, A0, A1, A2>,
                Default
            >
        { };
    };


    template< class To >
    struct object_generator :
        callable< object_generator<To> >
    {

        // PSTADE_CALLABLE_MAX_ARITY (primary)

        template< class Myself, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(PSTADE_CALLABLE_MAX_ARITY, class A, void) >
        struct apply :
            boost::mpl::BOOST_PP_CAT(apply_wrap, PSTADE_CALLABLE_MAX_ARITY)< To,
                BOOST_PP_ENUM_PARAMS(PSTADE_CALLABLE_MAX_ARITY, A)
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
            boost::mpl::apply_wrap1< To,
                A0
            >
        { };

        template< class Result, class A0 >
        Result call( A0& a0 ) const
        {
            return Result( a0 );
        }
                

        // 2ary-

    #define PSTADE_max_arity BOOST_PP_DEC(PSTADE_CALLABLE_MAX_ARITY)
        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_max_arity, <pstade/object_generator2.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_max_arity

    }; // object_generator



} // namespace pstade


PSTADE_CALLABLE_NULLARY_RESULT_TEMPLATE((pstade)(object_generator), 1)


#endif
#else
#define n BOOST_PP_ITERATION()


template< class Myself, BOOST_PP_ENUM_PARAMS(n, class A) >
struct apply< Myself, BOOST_PP_ENUM_PARAMS(n, A) > :
    boost::mpl::BOOST_PP_CAT(apply_wrap, n)< To,
        BOOST_PP_ENUM_PARAMS(n, A)
    >
{ };

template< class Result, BOOST_PP_ENUM_PARAMS(n, class A) >
Result call( PSTADE_PP_ENUM_REF_PARAMS_WITH_OBJECTS(n, A, a) ) const
{
    return Result( BOOST_PP_ENUM_PARAMS(n, a) );
}


#undef n
#endif
