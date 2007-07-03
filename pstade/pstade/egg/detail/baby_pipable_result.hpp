#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_BABY_PIPABLE_RESULT_HPP
#define PSTADE_EGG_DETAIL_BABY_PIPABLE_RESULT_HPP
#include "./prefix.hpp"


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
#include <pstade/deduced_const.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include "../apply_params.hpp"
#include "../config.hpp" // PSTADE_EGG_MAX_ARITY
#include "../function_fwd.hpp"
#include "../fuse.hpp"


namespace pstade { namespace egg { namespace detail {


    // 'boost::tuples::null_type' is a pod.

    template<class Base, class ArgTuple = boost::tuples::null_type>
    struct baby_pipable_result
    {
        typedef Base base_type;
        typedef ArgTuple arguments_type;

        Base m_base;
        ArgTuple m_arguments;

        Base base() const
        {
            return m_base;
        }

    // 0ary
        typedef
            function<baby_pipable_result>
        nullary_result_type;

        template<class Result>
        Result call() const
        {
            Result r = { { m_base } };
            return r;
        }

    // 1ary-
        template<class Myself, PSTADE_EGG_APPLY_PARAMS(A)>
        struct apply { }; // msvc warns if incomplete.

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_EGG_MAX_ARITY, <pstade/egg/detail/baby_pipable_result.hpp>))
        #include BOOST_PP_ITERATE()
    };


    template<class ArgTuple, class A> inline
    boost::tuples::cons<A&, ArgTuple> tuple_push_front(ArgTuple const& args, A& a)
    {
        return boost::tuples::cons<A&, ArgTuple>(a, args);
    }


    template<class A, class Base, class ArgTuple>
    struct result_of_output :
        result_of<
            typename result_of<op_fuse(Base const&)>::type(boost::tuples::cons<A&, ArgTuple>)
        >
    { };


    template<class A, class Base, class ArgTuple> inline
    typename result_of_output<A, Base, ArgTuple>::type
    operator|(A& a, function< baby_pipable_result<Base, ArgTuple> > const& pi)
    {
        return fuse(pi.baby().m_base)(detail::tuple_push_front(pi.baby().m_arguments, a));
    }

    template<class A, class Base, class ArgTuple> inline
    typename result_of_output<PSTADE_DEDUCED_CONST(A), Base, ArgTuple>::type
    operator|(A const& a, function< baby_pipable_result<Base, ArgTuple> > const& pi)
    {
        return fuse(pi.baby().m_base)(detail::tuple_push_front(pi.baby().m_arguments, a));
    }


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)>
    {
        typedef
            function<
                baby_pipable_result< Base, boost::tuples::tuple<PSTADE_PP_ENUM_PARAMS_WITH(n, A, &)> >
            >
        type;
    };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        typedef typename Result::baby_type baby_t;
        Result r = { { m_base, typename baby_t::arguments_type(BOOST_PP_ENUM_PARAMS(n, a)) } };
        return r;
    }


#undef n
#endif
