#ifndef PSTADE_OVEN_SEQUENCE_CAST_HPP
#define PSTADE_OVEN_SEQUENCE_CAST_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Same as:
//
// boost::copy_range


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>


namespace pstade { namespace oven {


template< class StlSequence, class Range > inline const
StlSequence sequence_cast(const Range& rng)
{
    return StlSequence(boost::begin(rng), boost::end(rng));
}


namespace sequence_cast_detail {


    template< class Range >
    struct temp
    {
        explicit temp(const Range& rng) :
            m_prng(&rng)
        { }

        template< class StlSequence >
        operator StlSequence () const
        {
            return oven::sequence_cast<StlSequence>(*m_prng);
        }

    private:
        const Range *m_prng;
    };


} // namespace sequence_cast_detail


template< class Range > inline const
sequence_cast_detail::temp<Range> sequence(const Range& rng)
{
    // Off Topic:
    //   When tmp is missing under GCC3.4.4, it ran a foul of strange behaviors
    //   if conversion template target is reference type.

    sequence_cast_detail::temp<Range> tmp(rng);
    return tmp;
}


} } // namespace pstade::oven


#endif
