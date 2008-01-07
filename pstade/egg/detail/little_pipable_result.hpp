#ifndef BOOST_PP_IS_ITERATING
#ifndef PSTADE_EGG_DETAIL_LITTLE_PIPABLE_RESULT_HPP
#define PSTADE_EGG_DETAIL_LITTLE_PIPABLE_RESULT_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/tuple/tuple.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/preprocessor.hpp>
#include <pstade/result_of.hpp>
#include "../apply_decl.hpp"
#include "../forward.hpp"
#include "../function_fwd.hpp"
#include "../fuse.hpp"
#include "../tuple/config.hpp"
#include "./is_front_by_of.hpp"


namespace pstade { namespace egg { namespace detail {


namespace little_pipable_resultns_ {


    namespace here = little_pipable_resultns_;


    // Fortunately, 'boost::tuples::null_type' is a POD type.

    template<class Base, class Strategy, class StrategyL, class ArgTuple = boost::tuples::null_type>
    struct little_pipable_result
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
            function<little_pipable_result, Strategy>
        nullary_result_type;

        template<class Result>
        Result call() const
        {
            Result r = { { m_base } };
            return r;
        }

    // 1ary-
    #define PSTADE_max_arity BOOST_PP_DEC(PSTADE_EGG_TUPLE_MAX_SIZE)
        template<class Myself, PSTADE_EGG_APPLY_DECL_PARAMS(PSTADE_max_arity, A)>
        struct PSTADE_EGG_APPLY_DECL;

        #define  BOOST_PP_ITERATION_PARAMS_1 (3, (1, PSTADE_max_arity, <pstade/egg/detail/little_pipable_result.hpp>))
        #include BOOST_PP_ITERATE()
    #undef  PSTADE_max_arity
    };


    template<class ArgTuple, class A> inline
    boost::tuples::cons<A&, ArgTuple> tuple_push_front(ArgTuple const& args, A& a)
    {
        return boost::tuples::cons<A&, ArgTuple>(a, args);
    }


    template<class A, class Base, class ArgTuple>
    struct result_of_output :
        result_of<
            typename result_of<T_fuse(Base const&)>::type(boost::tuples::cons<A&, ArgTuple>)
        >
    { };
    

    struct lookup_pipable_operator { };


    // operator|
    //   msvc-7.1 seems to need lazy_enable_if to keep return type as well-formed as possible.
    //

    template<class A, class Base, class Strategy, class StrategyL, class ArgTuple> inline
    typename lazy_enable_if< is_front_by_of2<by_perfect, by_ref, StrategyL>, result_of_output<A, Base, ArgTuple> >::type
    operator|(A& a, function<little_pipable_result<Base, Strategy, StrategyL, ArgTuple>, Strategy> const& pi)
    {
        return fuse(pi.little().m_base)(here::tuple_push_front(pi.little().m_arguments, a));
    }

    template<class A, class Base, class Strategy, class StrategyL, class ArgTuple> inline
    typename lazy_enable_if< is_front_by_of2<by_perfect, by_cref, StrategyL>, result_of_output<PSTADE_DEDUCED_CONST(A), Base, ArgTuple> >::type
    operator|(A const& a, function<little_pipable_result<Base, Strategy, StrategyL, ArgTuple>, Strategy> const& pi)
    {
        return fuse(pi.little().m_base)(here::tuple_push_front(pi.little().m_arguments, a));
    }

    // by_value
    template<class A, class Base, class Strategy, class StrategyL, class ArgTuple> inline
    typename lazy_enable_if< is_front_by_of<by_value, StrategyL>, result_of_output<A, Base, ArgTuple> >::type
    operator|(A a, function<little_pipable_result<Base, Strategy, StrategyL, ArgTuple>, Strategy> const& pi)
    {
        // For movable types, we can't turn `a` into `const reference`.
        return fuse(pi.little().m_base)(here::tuple_push_front(pi.little().m_arguments, a));
    }


    // operater|=
    //

    template<class A, class Base, class Strategy, class StrategyL, class ArgTuple> inline
    typename lazy_enable_if< is_front_by_of2<by_perfect, by_ref, StrategyL>, result_of_output<A, Base, ArgTuple> >::type
    operator|=(function<little_pipable_result<Base, Strategy, StrategyL, ArgTuple>, Strategy> const& pi, A& a)
    {
        return fuse(pi.little().m_base)(here::tuple_push_front(pi.little().m_arguments, a));
    }

    template<class A, class Base, class Strategy, class StrategyL, class ArgTuple> inline
    typename lazy_enable_if< is_front_by_of2<by_perfect, by_cref, StrategyL>, result_of_output<PSTADE_DEDUCED_CONST(A), Base, ArgTuple> >::type
    operator|=(function<little_pipable_result<Base, Strategy, StrategyL, ArgTuple>, Strategy> const& pi, A const& a)
    {
        return fuse(pi.little().m_base)(here::tuple_push_front(pi.little().m_arguments, a));
    }

    // by_value
    template<class A, class Base, class Strategy, class StrategyL, class ArgTuple> inline
    typename lazy_enable_if< is_front_by_of<by_value, StrategyL>, result_of_output<A, Base, ArgTuple> >::type
    operator|=(function<little_pipable_result<Base, Strategy, StrategyL, ArgTuple>, Strategy> const& pi, A a)
    {
        return fuse(pi.little().m_base)(here::tuple_push_front(pi.little().m_arguments, a));
    }


} // namespace little_pipable_resultns_


using little_pipable_resultns_::little_pipable_result;
using little_pipable_resultns_::lookup_pipable_operator;


} } } // namespace pstade::egg::detail


#endif
#else
#define n BOOST_PP_ITERATION()


    template<class Myself, BOOST_PP_ENUM_PARAMS(n, class A)>
    struct apply<Myself, BOOST_PP_ENUM_PARAMS(n, A)>
    {
        typedef
            function<
                little_pipable_result<
                    Base, Strategy, StrategyL,
                    // Arguments must be copied in case of by_value.
                    // Notice that Boost.Tuple doesn't work with movable types.
                    boost::tuples::tuple<PSTADE_EGG_FORWARD_ENUM_META_ARGS(n, A, Strategy)>
                >,
                Strategy
            >
        type;
    };

    template<class Result, BOOST_PP_ENUM_PARAMS(n, class A)>
    Result call(BOOST_PP_ENUM_BINARY_PARAMS(n, A, & a)) const
    {
        typedef typename Result::little_type little_t;
        Result r = { { m_base, typename little_t::arguments_type(BOOST_PP_ENUM_PARAMS(n, a)) } };
        return r;
    }


#undef n
#endif
