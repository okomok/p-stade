#ifndef PSTADE_OVEN_ITERATE_RANGE_HPP
#define PSTADE_OVEN_ITERATE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/optional.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/pass_by.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./generate_range.hpp"


namespace pstade { namespace oven {


namespace iterate_range_detail {


    template< class State, class UnaryFun >
    struct do_it
    {
        typedef boost::optional<State> result_type;

        result_type operator()()
        {
            if (m_beginning) {
                m_beginning = false;
                return m_state;
            }

            m_state = m_fun(m_state);
            return m_state;
        }

        do_it(State const& init, UnaryFun const& fun) :
            m_state(init), m_fun(fun), m_beginning(true)
        { }

    private:
        State m_state;
        UnaryFun m_fun;
        bool m_beginning;
    };


    template< class State, class UnaryFun, class Traversal >
    struct super_
    {
        typedef generate_range<do_it<State, UnaryFun>, Traversal> type;
    };


} // namespace iterate_range_detail


template<
    class State,
    class UnaryFun,
    class Traversal = boost::single_pass_traversal_tag
>
struct iterate_range :
    iterate_range_detail::super_<State, UnaryFun, Traversal>::type,
    private as_lightweight_proxy< iterate_range<State, UnaryFun, Traversal> >
{
    typedef State state_type;
    typedef UnaryFun function_type;

private:
    typedef typename iterate_range_detail::super_<State, UnaryFun, Traversal>::type super_t;
    typedef typename super_t::generator_type gen_t;

public:
    // The argument order follows 'std::accumulate'.
    iterate_range(State const& init, UnaryFun const& fun) :
        super_t(gen_t(init, fun))
    { }
};


namespace iterate_range_detail {


    struct baby_make
    {
        template< class Myself, class State, class UnaryFun, class Traversal = boost::single_pass_traversal_tag >
        struct apply
        {
            typedef typename pass_by_value<State>::type sta_t;
            typedef typename pass_by_value<UnaryFun>::type fun_t;
            typedef iterate_range<sta_t, fun_t, Traversal> const type;
        };

        template< class Result, class State, class UnaryFun, class Traversal >
        Result call(State const& init, UnaryFun& fun, Traversal)
        {
            return Result(init, fun);
        }

        template< class Result, class State, class UnaryFun >
        Result call(State const& init, UnaryFun& fun)
        {
            return Result(init, fun);
        }
    };


} // namespace iterate_range_detail


PSTADE_EGG_FUNCTION(make_iterate_range, iterate_range_detail::baby_make)
PSTADE_EGG_FUNCTION(iteration, iterate_range_detail::baby_make)


} } // namespace pstade::oven


#endif
