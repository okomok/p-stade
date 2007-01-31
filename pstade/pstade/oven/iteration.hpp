#ifndef PSTADE_OVEN_ITERATION_HPP
#define PSTADE_OVEN_ITERATION_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// The argument order follows 'std::accumulate'.


#include <boost/optional.hpp>
#include <pstade/callable.hpp>
#include <pstade/function.hpp>
#include <pstade/pass_by.hpp>
#include "./generation.hpp"


namespace pstade { namespace oven {


namespace iteration_detail {


    template< class State, class UnaryFun >
    struct op_gen
    {
        typedef
            boost::optional<State>
        result_type;

        result_type operator()()
        {
            if (m_beginning) {
                m_beginning = false;
                return m_state;
            }

            m_state = m_fun(m_state);
            return m_state;
        }

        op_gen(State const& init, UnaryFun const& fun) :
            m_state(init), m_fun(fun), m_beginning(true)
        { }

    private:
        State m_state;
        UnaryFun m_fun;
        bool m_beginning;
    };


    template< class State, class UnaryFun >
    struct baby
    {
        typedef
            iteration_detail::op_gen<
                typename pass_by_value<State>::type,
                typename pass_by_value<UnaryFun>::type
            >
        gen_t;

        typedef typename
            boost::result_of<
                op_generation(gen_t)
            >::type
        result;

        result call(State& init, UnaryFun& fun)
        {
            return generation(gen_t(init, fun));
        }
    };


} // namespace iteration_detail


PSTADE_FUNCTION(iteration, (iteration_detail::baby<_, _>))


} } // namespace pstade::oven


#endif
