#ifndef PSTADE_OVEN_RANGE_CAST_HPP
#define PSTADE_OVEN_RANGE_CAST_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <pstade/const_overloaded.hpp>
#include "./iterator_cast.hpp"
#include "./sub_range_base_type.hpp"


namespace pstade { namespace oven {


#if defined(BOOST_NO_MEMBER_TEMPLATES) || defined(BOOST_MSVC)
    #define PSTADE_OVEN_NO_AUTO_RANGE
#endif


template< class BaseIter, class Range > inline
typename const_overloaded<const boost::iterator_range<BaseIter>, Range>::type
range_cast(Range& rng)
{
    return boost::iterator_range<BaseIter>(
        oven::iterator_cast<BaseIter>(boost::begin(rng)),
        oven::iterator_cast<BaseIter>(boost::end(rng))
    );
}

    template< class BaseIter, class Range > inline
    const boost::iterator_range<BaseIter> range_cast(const Range& rng)
    {
        return boost::iterator_range<BaseIter>(
            oven::iterator_cast<BaseIter>(boost::begin(rng)),
            oven::iterator_cast<BaseIter>(boost::end(rng))
        );
    }


// iterator pair
template< class BaseIter, class Iterator > inline
boost::iterator_range<BaseIter> range_cast(Iterator first, Iterator last)
{
    return boost::iterator_range<BaseIter>(
        oven::iterator_cast<BaseIter>(first),
        oven::iterator_cast<BaseIter>(last)
    );
}


#if !defined(PSTADE_OVEN_NO_AUTO_RANGE)


namespace range_cast_detail {


    template< class Range >
    struct auto_range_type
    {
        explicit auto_range_type(Range& rng) :
            m_iter_rng(rng)
        { }

        template< class BaseIter >
        operator boost::iterator_range<BaseIter> () const
        {
            return oven::range_cast<BaseIter>(m_iter_rng);
        }

    private:
        typename sub_range_base<Range>::type m_iter_rng;
    };


} // namespace range_cast_detail


template< class Range > inline
range_cast_detail::auto_range_type<Range> auto_range(Range& rng)
{
    return range_cast_detail::auto_range_type<Range>(rng);
}

    template< class Range > inline
    range_cast_detail::auto_range_type<const Range> auto_range(const Range& rng)
    {
        return range_cast_detail::auto_range_type<const Range>(rng);
    }


// iterator pair
template< class Iterator > inline
range_cast_detail::auto_range_type< boost::iterator_range<Iterator> >
auto_range(Iterator first, Iterator last)
{
    boost::iterator_range<Iterator> rng(first, last);
    return range_cast_detail::auto_range_type< boost::iterator_range<Iterator> >(rng);
}


#endif // !defined(PSTADE_OVEN_NO_AUTO_RANGE)


} } // namespace pstade::oven


#endif
