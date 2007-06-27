#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_PIPABLE_RESULT_HPP
#define PSTADE_EGG_PIPABLE_RESULT_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/preprocessor.hpp>
#include "./apply_params.hpp"
#include "./detail/config.hpp" // PSTADE_EGG_MAX_ARITY
#include "./function.hpp"
#include "./fuse.hpp"


namespace pstade { namespace egg {


    namespace pipable_detail {


        namespace here = pipable_detail;


        // 'boost::tuples::null_type' is a pod.

        template<class Function, class ArgTuple = boost::tuples::null_type>
        struct pipable_result;


        template<class Function>
        struct pipe0
        {
            Function m_function;
        };

        template<class A, class Function> inline
        typename boost::result_of<Function(A&)>::type
        operator|(A& a, pipe0<Function> pi)
        {
            return pi.m_function(a);
        }

        template<class A, class Function> inline
        typename boost::result_of<Function(PSTADE_DEDUCED_CONST(A)&)>::type
        operator|(A const& a, pipe0<Function> pi)
        {
            return pi.m_function(a);
        }


        template<class Function, class ArgTuple>
        struct pipable_result
        {
            Function m_function;
            ArgTuple m_arguments;

            typedef Function base_type;
            typedef ArgTuple arguments_type;

            Function base() const
            {
                return m_function;
            }

            template<class Myself, PSTADE_EGG_APPLY_PARAMS(A)>
            struct apply
            { }; // msvc warns if incomplete.

        // 0ary
            typedef
                pipe0<Function>
            nullary_result_type;

            template<class Result>
            Result call() const
            {
                Result r = { m_function };
                return r;
            }

        // 1ary-
            #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_ARITY, <pstade/egg/pipable_result.hpp>))
            #include BOOST_PP_ITERATE()
        };


        template<class ArgTuple, class A> inline
        boost::tuples::cons<A&, ArgTuple>
        push_front(ArgTuple const& args, A& a)
        {
            return boost::tuples::cons<A&, ArgTuple>(a, args);
        }


        template<class A, class Function, class ArgTuple>
        struct result_of_output :
            boost::result_of<
                typename boost::result_of<op_fuse(Function const&)>::type(boost::tuples::cons<A&, ArgTuple>)
            >
        { };


        template<class A, class Function, class ArgTuple> inline
        typename result_of_output<A, Function, ArgTuple>::type
        operator|(A& a, function< pipable_result<Function, ArgTuple> > const& pi)
        {
            return fuse(pi.baby().m_function)(here::push_front(pi.baby().m_arguments, a));
        }

        template<class A, class Function, class ArgTuple> inline
        typename result_of_output<PSTADE_DEDUCED_CONST(A), Function, ArgTuple>::type
        operator|(A const& a, function< pipable_result<Function, ArgTuple> > const& pi)
        {
            return fuse(pi.baby().m_function)(here::push_front(pi.baby().m_arguments, a));
        }


    } // namespace pipable_detail


    using pipable_detail::pipable_result;


} } // namespace pstade::egg


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)>
    {
        typedef
            function<
                pipable_result< Function, boost::tuples::tuple<PSTADE_PP_ENUM_PARAMS_WITH(n, A, &)> >
            >
        type;
    };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        typedef typename Result::baby_type baby_t;
        Result r = { { m_function, typename baby_t::arguments_type(BOOST_PP_ENUM_PARAMS(n, a)) } };
        return r;
    }


#undef n
#endif
