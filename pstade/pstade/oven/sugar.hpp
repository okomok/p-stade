#ifndef PSTADE_OVEN_SUGAR_HPP
#define PSTADE_OVEN_SUGAR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/result_of.hpp>
#include <pstade/constant.hpp>
#include "./cycled.hpp"
#include "./iter_range.hpp"
#include "./jointed.hpp"


namespace pstade { namespace oven {


typedef op_make_iter_range op_as_term;
PSTADE_CONSTANT(as_term, (op_as_term))


// +

template< class It1, class In1 > inline
typename boost::result_of<
    op_make_cycled(iter_range<It1, In1> const&)
>::type
operator+(iter_range<It1, In1> const& rng1)
{
    return make_cycled(rng1);
}


// >>

template< class It1, class In1, class It2, class In2 > inline
typename boost::result_of<
    op_make_jointed(iter_range<It1, In1> const&, iter_range<It2, In2> const&)
>::type
operator>>(iter_range<It1, In1> const& rng1, iter_range<It2, In2> const& rng2)
{
    return make_jointed(rng1, rng2);
}


namespace sugar {


    // In these cases, 'result_of' may be ill-formed in overload-resolution.
    // You must guarantee to be well-formed and write 'using namespace sugar;'.


    // >>

    template< class It1, class In1, class Range2 > inline
    typename boost::result_of<
        op_make_jointed(iter_range<It1, In1> const&, Range2&)
    >::type
    operator>>(iter_range<It1, In1> const& rng1, Range2& rng2)
    {
        return make_jointed(rng1, rng2);
    }

    template< class It1, class In1, class Range2 > inline
    typename boost::result_of<
        op_make_jointed(iter_range<It1, In1> const&, Range2 const&)
    >::type
    operator>>(iter_range<It1, In1> const& rng1, Range2 const& rng2)
    {
        return make_jointed(rng1, rng2);
    }

    template< class Range1, class It2, class In2 > inline
    typename boost::result_of<
        op_make_jointed(Range1&, iter_range<It2, In2> const&)
    >::type
    operator>>(Range1& rng1, iter_range<It2, In2> const& rng2)
    {
        return make_jointed(rng1, rng2);
    }

    template< class Range1, class It2, class In2 > inline
    typename boost::result_of<
        op_make_jointed(Range1 const&, iter_range<It2, In2> const&)
    >::type
    operator>>(Range1 const& rng1, iter_range<It2, In2> const& rng2)
    {
        return make_jointed(rng1, rng2);
    }


} // namespace sugar


} } // namespace pstade::oven


#endif
