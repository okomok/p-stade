#ifndef PSTADE_OVEN_SUGAR_HPP
#define PSTADE_OVEN_SUGAR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/prelude.hpp"
#include <boost/utility/result_of.hpp>
#include <pstade/constant.hpp>
#include "./as_range.hpp" // inclusion guaranteed
#include "./cycled.hpp"
#include "./iter_range.hpp"
#include "./jointed.hpp"


namespace pstade { namespace oven {


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


    // Even if either of the parameters is 'iter_range',
    // it may be ill-formed by 'result_of' in overload-resolution.
    // Hence these are placed in separated namespace 'sugar'.


    // +

    template< class Range1 > inline
    typename boost::result_of<
        op_make_cycled(Range1&)
    >::type
    operator+(Range1& rng1)
    {
        return make_cycled(rng1);
    }

    template< class Range1 > inline
    typename boost::result_of<
        op_make_cycled(Range1 const&)
    >::type
    operator+(Range1 const& rng1)
    {
        return make_cycled(rng1);
    }


    // >>

    template< class Range1, class Range2 > inline
    typename boost::result_of<
        op_make_jointed(Range1&, Range2&)
    >::type
    operator>>(Range1& rng1, Range2& rng2)
    {
        return make_jointed(rng1, rng2);
    }

    template< class Range1, class Range2 > inline
    typename boost::result_of<
        op_make_jointed(Range1&, Range2 const&)
    >::type
    operator>>(Range1& rng1, Range2 const& rng2)
    {
        return make_jointed(rng1, rng2);
    }

    template< class Range1, class Range2 > inline
    typename boost::result_of<
        op_make_jointed(Range1 const&, Range2&)
    >::type
    operator>>(Range1 const& rng1, Range2& rng2)
    {
        return make_jointed(rng1, rng2);
    }

    template< class Range1, class Range2 > inline
    typename boost::result_of<
        op_make_jointed(Range1 const&, Range2 const&)
    >::type
    operator>>(Range1 const& rng1, Range2 const& rng2)
    {
        return make_jointed(rng1, rng2);
    }


} // namespace sugar


} } // namespace pstade::oven


#endif
