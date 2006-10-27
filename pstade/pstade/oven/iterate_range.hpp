#ifndef PSTADE_OVEN_ITERATE_RANGE_HPP
#define PSTADE_OVEN_ITERATE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/optional.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/pass_by.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./generate_range.hpp"


namespace pstade { namespace oven {


namespace iterate_range_detail {


    template< class State, class UnaryFun >
    struct gen_fun
    {
        typedef boost::optional<State> result_type;

        result_type operator()()
        {
            m_state = m_fun(m_state);
            return m_state;
        }

        gen_fun(State const& state, UnaryFun const& fun) :
            m_state(state), m_fun(fun)
        { }

    private:
        State m_state;
        UnaryFun m_fun;
    };


    template< class State, class UnaryFun >
    struct super_
    {
        typedef generate_range< gen_fun<State, UnaryFun> > type;
    };


} // namespace iterate_range_detail


template< class State, class UnaryFun >
struct iterate_range :
    iterate_range_detail::super_<State, UnaryFun>::type,
    private as_lightweight_proxy< iterate_range<State, UnaryFun> >
{
    typedef State state_type;
    typedef UnaryFun function_type;

private:
    typedef typename iterate_range_detail::super_<State, UnaryFun>::type super_t;
    typedef typename super_t::generator_type gen_t;

public:
    iterate_range(State const& state, UnaryFun fun) :
        super_t(gen_t(state, fun))
    { }
};


namespace iterate_range_detail {


    struct baby_make
    {
        template< class Myself, class State, class UnaryFun >
        struct apply
        {
            typedef typename pass_by_value<State>::type sta_t;
            typedef typename pass_by_value<UnaryFun>::type fun_t;
            typedef iterate_range<sta_t, fun_t> const type;
        };

        template< class Result, class State, class UnaryFun >
        Result call(State const& state, UnaryFun& fun)
        {
            return Result(state, fun);
        }
    };


} // namespace iterate_range_detail


PSTADE_EGG_FUNCTION(make_iterate_range, iterate_range_detail::baby_make)
PSTADE_EGG_FUNCTION(iteration, iterate_range_detail::baby_make)


} } // namespace pstade::oven


#endif
