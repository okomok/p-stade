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


#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/nonassignable.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/singleton.hpp>
#include <pstade/tupled.hpp>
#include <pstade/untupled.hpp>


namespace pstade {


    namespace pipable_detail {


        template< class Function, class Arguments = boost::tuples::tuple<> >
        struct tupled_baby_pipe :
            private nonassignable
        {
            template< class Myself, class Arguments_ >
            struct apply
            {
                typedef tupled_baby_pipe<Function, Arguments_> type;
            };

            template< class Result, class Arguments_ >
            Result call(Arguments& args) const
            {
                return Result(m_fun, args);
            }

            // 0ary
            typedef tupled_baby_pipe const& nullary_result_type;

            template< class Result >
            Result call( ) const
            {
                return *this;
            }

            explicit tupled_baby_pipe() // DefaultConstructible if 'Function' is.
            { }

            explicit tupled_baby_pipe(Function const& fun, Arguments const& args = Arguments()) :
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
        };


        template< class Function, class Arguments = boost::tuples::tuple<> >
        struct pipe_of
        {
            typedef
                egg::function<
                    tupled_baby_pipe<Function, Arguments>
                >
            tupled_pipe;

            typedef typename
                boost::result_of<untupled(tupled_pipe)>::type
            type;
        };


        template< class Arguments, class A > inline
        boost::tuples::cons<A&, Arguments>
        push_front(Arguments const& args, A& a)
        {
            return boost::tuples::cons<A&, Arguments>(a, args);
        };


        template< class A, class Function, class Arguments >
        struct result_of_piping
        {
            typedef typename
                boost::result_of<tupled_fun(Function)>::type
            tupled_t;

            typedef
                boost::tuples::cons<A&, Arguments>
            args_t;

            typedef typename
                boost::result_of<tupled_t(args_t)>::type
            type;
        };


        template< class A, class Function, class Arguments > inline
        typename result_of_piping<A, Function, Arguments>::type
        operator|(A& a, typename pipe_of<Function, Arguments> const& pi)
        {
            return pstade::tupled(pi.base().base())(
                pipable_detail::push_front(pi.base().arguments(), a)
            );
        };

        // prefer 'add_const' for VC++7.1.
        template< class A, class Function, class Arguments > inline
        typename result_of_piping<typename boost::add_const<A>::type, Function, Arguments>::type
        operator|(A const& a, tupled_baby_pipe<Function, Arguments> const& pi)
        {
            return pstade::tupled(pi.base().base())(
                pipable_detail::push_front(pi.base().arguments(), a)
            );
        };


        struct baby
        {
            template< class Myself, class Function >
            struct apply :
                pipe_of<typename pass_by_value<Function>::type>
            { };

            template< class Result, class Function >
            Result call(Function& fun) const
            {
                typedef typename Result::base_type tupled_pipe;
                return pstade::untupled(tupled_pipe(fun));
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
