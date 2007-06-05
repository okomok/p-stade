#ifndef PSTADE_OVEN_ITERATION_HPP
#define PSTADE_OVEN_ITERATION_HPP
#include "./prelude.hpp"


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


#include <pstade/function.hpp>
#include <pstade/pass_by.hpp>
#include "./detail/iterate_iterator.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace iteration_detail {


    template< class State, class UnaryFun >
    struct baby
    {
        typedef
            detail::iterate_iterator<
                typename pass_by_value<State>::type,
                typename pass_by_value<UnaryFun>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(State& init, UnaryFun& fun) const
        {
            return result_type(
                iter_t(init, fun, false),
                iter_t(init, fun, true)
            );
        }
    };


} // namespace iteration_detail


PSTADE_FUNCTION(iteration, (iteration_detail::baby<_, _>))


} } // namespace pstade::oven


#endif
