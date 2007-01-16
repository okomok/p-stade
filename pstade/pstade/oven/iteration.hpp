#ifndef PSTADE_OVEN_ITERATION_HPP
#define PSTADE_OVEN_ITERATION_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// The argument order follows 'std::accumulate'.


#include <boost/optional.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/unused_parameter.hpp>
#include "./generation.hpp"


namespace pstade { namespace oven {


namespace iteration_detail {


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


} // namespace iteration_detail


struct op_iteration :
    callable<op_iteration>
{
    template< class Myself, class State, class UnaryFun, class Traversal = boost::single_pass_traversal_tag >
    struct apply
    {
        typedef
            iteration_detail::do_it<
                typename pass_by_value<State>::type,
                typename pass_by_value<UnaryFun>::type
            >
        gen_t;

        typedef typename
            boost::result_of<
                op_generation_copied(gen_t)
            >::type
        type;
    };

    template< class Result, class State, class UnaryFun >
    Result call(State const& init, UnaryFun fun, unused_parameter = 0) const
    {
        return generation_copied(iteration_detail::do_it<State, UnaryFun>(init, fun));
    }
};


PSTADE_CONSTANT(iteration, (op_iteration))


} } // namespace pstade::oven


#endif
