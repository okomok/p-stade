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


// Note:
//
// You may say preprocessors could be removed by using
// the way shown at "./compose.hpp".
// But such implementation is not as small as the following.
// Also, we must know the exact type passed to 'operator|'.


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/const.hpp>
#include <pstade/constant.hpp>
#include <pstade/nonassignable.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/tupled.hpp>


namespace pstade {


    namespace pipable_detail {


        template< class Function, class Arguments = boost::tuples::tuple<> >
        struct pipe :
            callable< pipe<Function, Arguments>, pipe<Function, Arguments> const& >,
            private nonassignable
        {

            // PSTADE_CALLABLE_MAX_ARITY (primary)
            template< class Myself, BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(PSTADE_CALLABLE_MAX_ARITY, class A, void) >
            struct apply
            {
                typedef pipe< Function,
                    // tuple of references!
                    boost::tuples::tuple< PSTADE_PP_ENUM_REF_PARAMS(PSTADE_CALLABLE_MAX_ARITY, A) >
                > type;
            };

            template< class Result, BOOST_PP_ENUM_PARAMS(PSTADE_CALLABLE_MAX_ARITY, class A) >
            Result call( PSTADE_PP_ENUM_REF_PARAMS_WITH_OBJECTS(PSTADE_CALLABLE_MAX_ARITY, A, a) ) const
            {
                return Result( m_fun,
                    typename Result::arguments_type( BOOST_PP_ENUM_PARAMS(PSTADE_CALLABLE_MAX_ARITY, a) )
                );
            }

            // 0ary
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
        #define PSTADE_max_arity BOOST_PP_DEC(PSTADE_CALLABLE_MAX_ARITY)
            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (2, PSTADE_max_arity, <pstade/pipable.hpp>))
            #include BOOST_PP_ITERATE()
        #undef  PSTADE_max_arity

            explicit pipe() // DefaultConstructible if 'Function' is.
            { }

            explicit pipe(Function const& fun, Arguments const& args = Arguments()) :
                m_fun(fun), m_args(args)
            { }

            typedef Function base_type;
            typedef Arguments arguments_type;

            Function const& base() const
            {
                return m_fun;
            }

            Arguments const& arguments() const
            {
                return m_args;
            }

        private:
            Function m_fun;
            Arguments m_args;

        }; // struct pipe


        template< class Arguments, class A > inline
        boost::tuples::cons<A&, Arguments>
        push_front(Arguments const& args, A& a)
        {
            return boost::tuples::cons<A&, Arguments>(a, args);
        };


        template< class A, class Function, class Arguments >
        struct result_of_output
        {
            typedef typename boost::result_of<op_tupled(Function)>::type tupled_f;
            typedef boost::tuples::cons<A&, Arguments> args_t;
            typedef typename boost::result_of<tupled_f(args_t)>::type type;
        };

        template< class Result, class A, class Pipe > inline
        Result output(A& a, Pipe const& pi)
        {
            return pstade::tupled(pi.base())(
                pipable_detail::push_front(pi.arguments(), a)
            );
        }


        template< class A, class Function, class Arguments > inline
        typename result_of_output<A, Function, Arguments>::type
        operator|(A& a, pipe<Function, Arguments> const& pi)
        {
            return pipable_detail::output<
                typename result_of_output<A, Function, Arguments>::type
            >(a, pi);
        };

        template< class A, class Function, class Arguments > inline
        typename result_of_output<PSTADE_CONST(A), Function, Arguments>::type
        operator|(A const& a, pipe<Function, Arguments> const& pi)
        {
            return pipable_detail::output<
                typename result_of_output<PSTADE_CONST(A), Function, Arguments>::type
            >(a, pi);
        };


    } // namespace pipable_detail


    typedef object_generator< pipable_detail::pipe<object_arg1> > op_pipable;
    PSTADE_CONSTANT(pipable, op_pipable)


    #define PSTADE_PIPABLE(Object, Function) \
        PSTADE_CONSTANT(Object, boost::result_of<pstade::op_pipable(Function)>::type)
    /**/


} // namespace pstade


PSTADE_CALLABLE_NULLARY_RESULT_TEMPLATE((pstade)(pipable_detail)(pipe), 2)


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
