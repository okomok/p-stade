#ifndef PSTADE_OVEN_ITERATION_HPP
#define PSTADE_OVEN_ITERATION_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// The argument order follows 'std::accumulate'.
//
// 'scanned' with 'counting' can't implement this,
// because 'counting' can't represent "infinity".


#include <utility> // pair
#include <boost/optional/optional.hpp>
#include <pstade/egg/adapt.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./unfoldr.hpp"


namespace pstade { namespace oven {


namespace iteration_detail {


    template< class State, class UnaryFun >
    struct just_call
    {
        typedef just_call is_pure;

        typedef
            boost::optional< std::pair<State, State> >
        result_type;

        result_type operator()(State const& b) const
        {
            return std::make_pair(b, m_fun(b));
        }

        explicit just_call()
        { }

        explicit just_call(UnaryFun fun) :
            m_fun(fun)
        { }

    private:
        UnaryFun m_fun;
    };


    template< class State, class UnaryFun >
    struct base
    {
        typedef
            just_call<
                typename pass_by_value<State>::type,
                typename pass_by_value<UnaryFun>::type
            >
        just_call_t;

        typedef typename
            result_of<
                op_unfoldr(State&, just_call_t)
            >::type
        result_type;

        result_type operator()(State& init, UnaryFun& fun) const
        {
            return unfoldr(init, just_call_t(fun));
        }
    };


} // namespace iteration_detail


typedef PSTADE_EGG_ADAPT((iteration_detail::base<boost::mpl::_, boost::mpl::_>)) op_iteration;
PSTADE_POD_CONSTANT((op_iteration), iteration) = PSTADE_EGG_ADAPT_INITIALIZER();


} } // namespace pstade::oven


#endif
