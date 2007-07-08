#ifndef PSTADE_OVEN_MOVED_HPP
#define PSTADE_OVEN_MOVED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Pending...
//


// Note:
//
// Is this range is really needed?
// 'transformed(move)' seems enough?


#include <pstade/miniboost/move.hpp>
#include <boost/mpl/if.hpp>
#include <pstade/result_of.hpp>
#include "./concepts.hpp"
#include "./detail/base_to_adaptor.hpp"
#include "./range_value.hpp"
#include "./transformed.hpp"


namespace pstade { namespace oven {


namespace moved_detail {


    template< class Value >
    struct op_move
    {
        typedef typename
            boost::mpl::if_< boost::is_movable<Value>,
                Value,
                Value&
            >::type
        result_type;

        template< class T >
        result_type operator()(T& x) const
        {
            return boost::move(x);
        }
    };


    template< class Range >
    struct base
    {
        typedef
            op_move<typename range_value<Range>::type>
        fun_t;

        typedef typename
            result_of<
                op_make_transformed(Range&, fun_t)
            >::type
        result_type;

        result_type operator()(Range& rng) const
        {
            return make_transformed(rng, fun_t());
        }
    };


} // namespace moved_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(moved, (moved_detail::base<_>))


} } // namespace pstade::oven


#endif
