#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_PIPABLE_HPP
#define PSTADE_PIPABLE_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of: adaptor_base at Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/nonassignable.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/singleton.hpp>
#include <pstade/tupled.hpp>


namespace pstade {


    namespace pipable_detail {


        template< class Function, class Arguments = boost::tuples::tuple<> >
        struct pipe :
            private nonassignable
        {

            typedef Function function_type;
            typedef Arguments arguments_type;

            // PSTADE_EGG_MAX_ARITY (primary)
            template< class Myself, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(PSTADE_EGG_MAX_ARITY, class A, void) >
            struct apply
            {
                typedef pipe< Function,
                    // tuple of references!
                    boost::tuples::tuple< PSTADE_PP_ENUM_REF_PARAMS(PSTADE_EGG_MAX_ARITY, A) >
                > type;
            };

            template< class Result, BOOST_PP_ENUM_PARAMS(PSTADE_EGG_MAX_ARITY, class A) >
            Result call( PSTADE_PP_ENUM_REF_PARAMS_WITH_OBJECTS(PSTADE_EGG_MAX_ARITY, A, a) ) const
            {
                return Result( m_fun,
                    typename Result::arguments_type( BOOST_PP_ENUM_PARAMS(PSTADE_EGG_MAX_ARITY, a) )
                );
            }

            // 0ary
            typedef
                pipe const&
            nullary_result_type;

            template< class Result >
            Result call( ) const
            {
                return *this;
            }

            // 1ary
            template< class Myself, class A0 >
            struct apply< Myself, A0 >
            {
                typedef pipe< Function,
                    boost::tuples::tuple< A0& >
                > type;
            };

            template< class Result, class A0 >
            Result call( A0& a0 ) const
            {
                return Result( m_fun,
                    typename Result::arguments_type( a0 )
                );
            }

            // 2ary-
        #define PSTADE_max_arity BOOST_PP_DEC(PSTADE_EGG_MAX_ARITY)
            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_max_arity, <pstade/pipable.hpp>))
            #include BOOST_PP_ITERATE()
        #undef  PSTADE_max_arity

            explicit pipe() // DefaultConstructible if 'Function' is.
            { }

            explicit pipe(Function const& fun, Arguments const& args = Arguments()) :
                m_fun(fun), m_args(args)
            { }

            Function const& function() const
            {
                return m_fun;
            }

            Arguments const& arguments() const
            {
                return m_args;
            }

        private:
            mutable Function m_fun;
            Arguments m_args;

        }; // struct pipe


        template< class Tuple, class A >
        struct result_of_push_front
        {
            typedef boost::tuples::cons<A&, Tuple> type;
        };

        template< class Tuple, class A > inline
        typename result_of_push_front<Tuple, A>::type
        push_front(Tuple const& tup, A& a)
        {
            return boost::tuples::cons<A&, Tuple>(a, tup);
        };


        template< class A, class Function, class Arguments >
        struct result_of_piping
        {
            typedef typename
                boost::result_of<tupled_fun(Function)>::type
            tupled_t;

            typedef typename
                result_of_push_front<Arguments, A>::type
            args_t;

            typedef typename
                boost::result_of<tupled_t(args_t)>::type
            type;
        };


        template< class A, class Function, class Arguments > inline
        typename result_of_piping<A, Function, Arguments>::type
        operator|(A& a, pipe<Function, Arguments> const& pi)
        {
            return pstade::tupled(pi.function())(
                pipable_detail::push_front(pi.arguments(), a)
            );
        };

        // prefer 'add_const' for VC++7.1.
        template< class A, class Function, class Arguments > inline
        typename result_of_piping<typename boost::add_const<A>::type, Function, Arguments>::type
        operator|(A const& a, pipe<Function, Arguments> const& pi)
        {
            return pstade::tupled(pi.function())(
                pipable_detail::push_front(pi.arguments(), a)
            );
        };


        struct baby
        {
            template< class Myself, class Function >
            struct apply
            {
                typedef typename pass_by_value<Function>::type fun_t;
                typedef egg::function< pipe<fun_t> > type;
            };

            template< class Result, class Function >
            Result call(Function& fun) const
            {
                return Result(fun);
            }
        };


    } // namespace pipable_detail


    PSTADE_EGG_FUNCTION(pipable, pipable_detail::baby)


    #define PSTADE_PIPABLE(Object, Function) \
        PSTADE_SINGLETON_CONST( \
            boost::result_of<pstade::pipable_fun(Function)>::type, \
            Object \
        ) \
    /**/


} // namespace pstade


#endif
#else
#define n BOOST_PP_ITERATION()


template< class Myself, BOOST_PP_ENUM_PARAMS(n, class A) >
struct apply< Myself, BOOST_PP_ENUM_PARAMS(n, A) >
{
    typedef pipe< Function,
        boost::tuples::tuple< PSTADE_PP_ENUM_REF_PARAMS(n, A) >
    > type;
};

template< class Result, BOOST_PP_ENUM_PARAMS(n, class A) >
Result call( PSTADE_PP_ENUM_REF_PARAMS_WITH_OBJECTS(n, A, a) ) const
{
    return Result( m_fun,
        typename Result::arguments_type( BOOST_PP_ENUM_PARAMS(n, a) )
    );
}


#undef n
#endif
