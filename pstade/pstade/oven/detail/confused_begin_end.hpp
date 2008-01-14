#ifndef PSTADE_OVEN_DETAIL_CONFUSED_BEGIN_END_HPP
#define PSTADE_OVEN_DETAIL_CONFUSED_BEGIN_END_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Works around a defect of fusion::transform_view + fusion::value_of.
// See http://svn.boost.org/trac/boost/ticket/1396


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/pod_constant.hpp>
#include "../range_iterator.hpp"


namespace pstade { namespace oven { namespace detail {


struct T_confused_begin
{
    template< class Signature >
    struct result;

    template< class This, class Range >
    struct result<This(Range&)> :
        range_iterator<Range>
    { };

    template< class This, class Range >
    struct result<This(Range)> : // rvalue
        range_iterator<Range> // cheating!
    { };

    template< class Range >
    typename range_iterator<Range>::type operator()(Range& rng) const
    {
        return boost::begin(rng);
    }

    template< class Range >
    typename range_iterator<Range const>::type operator()(Range const& rng) const
    {
        return boost::begin(rng);
    }
};

PSTADE_POD_CONSTANT((T_confused_begin), confused_begin) = {};


struct T_confused_end
{
    template< class Signature >
    struct result;

    template< class This, class Range >
    struct result<This(Range&)> :
        range_iterator<Range>
    { };

    template< class This, class Range >
    struct result<This(Range)> : // rvalue
        range_iterator<Range> // cheating!
    { };

    template< class Range >
    typename range_iterator<Range>::type operator()(Range& rng) const
    {
        return boost::end(rng);
    }

    template< class Range >
    typename range_iterator<Range const>::type operator()(Range const& rng) const
    {
        return boost::end(rng);
    }
};

PSTADE_POD_CONSTANT((T_confused_end), confused_end) = {};


} } } // namespace pstade::oven::detail


#endif
