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


#include <boost/optional/optional.hpp>
#include <pstade/egg/deferred.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pod_constant.hpp>
#include <pstade/result_of.hpp>
#include "./unfold.hpp"


namespace pstade { namespace oven {


namespace iteration_detail {


    template< class State >
    struct just
    {
        typedef
            boost::optional<State>
        result_type;

        result_type operator()(State const& s) const
        {
            return s;
        }
    };


    template< class State, class UnaryFun >
    struct base
    {
        typedef typename
            pass_by_value<State>::type
        state_t;

        typedef typename
            result_of<
                T_unfold(State&, just<state_t>, UnaryFun&)
            >::type
        result_type;

        result_type operator()(State& init, UnaryFun& fun) const
        {
            return unfold(init, just<state_t>(), fun);
        }
    };


} // namespace iteration_detail


typedef PSTADE_EGG_DEFER((iteration_detail::base<boost::mpl::_, boost::mpl::_>)) T_iteration;
PSTADE_POD_CONSTANT((T_iteration), iteration) = PSTADE_EGG_DEFERRED;


} } // namespace pstade::oven


#endif
