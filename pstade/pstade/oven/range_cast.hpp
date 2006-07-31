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
#include <boost/type_traits/add_const.hpp>
#include <pstade/const_overloaded.hpp>
#include "./iterator_cast.hpp"
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


#if defined(BOOST_NO_MEMBER_TEMPLATES) || defined(BOOST_MSVC)
    #define PSTADE_OVEN_NO_BASE_RANGE
#endif


template< class BaseIter, class Range > inline
typename const_overloaded<boost::iterator_range<BaseIter>, Range>::type const
range_cast(Range& rng)
{
    return boost::iterator_range<BaseIter>(
        oven::iterator_cast<BaseIter>(boost::begin(rng)),
        oven::iterator_cast<BaseIter>(boost::end(rng))
    );
}

    template< class BaseIter, class Range > inline
    boost::iterator_range<BaseIter> const
    range_cast(const Range& rng)
    {
        return boost::iterator_range<BaseIter>(
            oven::iterator_cast<BaseIter>(boost::begin(rng)),
            oven::iterator_cast<BaseIter>(boost::end(rng))
        );
    }


// iterator pair
template< class BaseIter, class Iterator > inline
boost::iterator_range<BaseIter> const
range_cast(Iterator const& first, Iterator const& last)
{
    return boost::iterator_range<BaseIter>(
        oven::iterator_cast<BaseIter>(first),
        oven::iterator_cast<BaseIter>(last)
    );
}


#if !defined(PSTADE_OVEN_NO_BASE_RANGE)


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
range_cast_detail::auto_range_type<Range> const
base_range(Range& rng)
{
    return range_cast_detail::auto_range_type<Range>(rng);
}

    template< class Range > inline
    range_cast_detail::auto_range_type<typename boost::add_const<Range>::type> const
    base_range(Range const& rng)
    {
        return range_cast_detail::auto_range_type<typename boost::add_const<Range>::type>(rng);
    }


// iterator pair
template< class Iterator > inline
range_cast_detail::auto_range_type< boost::iterator_range<Iterator> > const
base_range(Iterator const& first, Iterator const& last)
{
    boost::iterator_range<Iterator> rng(first, last);
    return range_cast_detail::auto_range_type< boost::iterator_range<Iterator> >(rng);
}


#endif // !defined(PSTADE_OVEN_NO_BASE_RANGE)


} } // namespace pstade::oven


#endif
