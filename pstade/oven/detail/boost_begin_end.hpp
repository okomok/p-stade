#ifndef PSTADE_OVEN_DETAIL_BOOST_BEGIN_END_HPP
#define PSTADE_OVEN_DETAIL_BOOST_BEGIN_END_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// If Boost.Range doesn't work around a bug of msvc-7.1 array,
// we will need this...


#include <cstddef> // size_t
#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/deduced_const.hpp>
#include <pstade/pod_constant.hpp>
#include "../range_iterator.hpp"


namespace pstade { namespace oven {


// boost_begin
//

struct boost_begin_t
{
    template< class Range >
    typename range_iterator<Range>::type
    operator()(Range& rng) const
    {
        return boost::begin(rng);
    }

    template< class Range >
    typename range_iterator<PSTADE_DEDUCED_CONST(Range)>::type
    operator()(Range const& rng) const
    {
        return boost::begin(rng);
    }

#if BOOST_WORKAROUND(BOOST_MSVC, == 1310) // msvc-7.1
    template< class T, std::size_t N >
    T *
    operator()(T (&arr)[N]) const
    {
        return boost::addressof(arr[0]);
    }
#endif
};

PSTADE_POD_CONSTANT((boost_begin_t), boost_begin) = {};


// boost_end
//

struct boost_end_t
{
    template< class Range >
    typename range_iterator<Range>::type
    operator()(Range& rng) const
    {
        return boost::end(rng);
    }

    template< class Range >
    typename range_iterator<PSTADE_DEDUCED_CONST(Range)>::type
    operator()(Range const& rng) const
    {
        return boost::end(rng);
    }

#if BOOST_WORKAROUND(BOOST_MSVC, == 1310) // msvc-7.1
    template< class T, std::size_t N >
    T *
    operator()(T (&arr)[N]) const
    {
        return boost::addressof(arr[0]) + N;
    }
#endif
};

PSTADE_POD_CONSTANT((boost_end_t), boost_end) = {};


} } // namespace pstade::oven


#endif
