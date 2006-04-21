#ifndef PSTADE_OVEN_FILTER_RANGE_HPP
#define PSTADE_OVEN_FILTER_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See: Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/filter_iterator.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <boost/type_traits/add_const.hpp>
#include <pstade/const_overloaded.hpp>
#include "./is_lightweight_proxy.hpp"


namespace pstade { namespace oven {


template< class Predicate, class Range >
struct filter_range :
    boost::iterator_range<
        boost::filter_iterator<
            Predicate,
            typename boost::range_result_iterator<Range>::type
        >
    >
{
    typedef typename boost::range_result_iterator<Range>::type base_iterator;

private:
    typedef boost::filter_iterator<Predicate, base_iterator> iter_t;
    typedef boost::iterator_range<iter_t> super_t;

public:
    explicit filter_range(Predicate pred, Range& rng) :
        super_t(
            iter_t(pred, boost::begin(rng), boost::end(rng)),
            iter_t(pred, boost::end(rng), boost::end(rng))
        )
    { }

    // Note:
    //   make_filter_iterator without predicate object fails under eVC4.

    // seems an inconsistent interface to me, though Biscuit loves this style.
    explicit filter_range(Range& rng) :
        super_t(
            iter_t(boost::begin(rng), boost::end(rng)),
            iter_t(boost::end(rng), boost::end(rng))
        )
    { }
};


template< class Predicate, class Range > inline
const filter_range<Predicate, Range>
make_filter_range(Predicate pred, Range& rng)
{
    return filter_range<Predicate, Range>(pred, rng);
}

    template< class Predicate, class Range > inline
    const filter_range<Predicate, typename boost::add_const<Range>::type>
    make_filter_range(Predicate pred, const Range& rng)
    {
        return filter_range<Predicate, typename boost::add_const<Range>::type>(pred, rng);
    }


// without object
template< class Predicate, class Range > inline
typename const_overloaded<const filter_range<Predicate, Range>, Range>::type
make_filter_range(Range& rng)
{
    return filter_range<Predicate, Range>(rng);
}

    template< class Predicate, class Range > inline
    const filter_range<Predicate, typename boost::add_const<Range>::type>
    make_filter_range(const Range& rng)
    {
        return filter_range<Predicate, typename boost::add_const<Range>::type>(rng);
    }


namespace filter_range_detail {


    template< class Predicate >
    struct adaptor
    {
        adaptor(Predicate pred) : m_pred(pred) { }
        Predicate m_pred;
    };


    template< class Predicate, class Range > inline
    filter_range<Predicate, Range>
    operator|(Range& rng, adaptor<Predicate> ad)
    {
        return oven::make_filter_range(ad.m_pred, rng);
    }

    template< class Predicate, class Range > inline
    filter_range<Predicate, typename boost::add_const<Range>::type>
    operator|(const Range& rng, adaptor<Predicate> ad)
    {
        return oven::make_filter_range(ad.m_pred, rng);
    }


    template< class Predicate >
    struct adaptor_without_object
    { };


    template< class Predicate, class Range > inline
    const filter_range<Predicate, Range>
    operator|(Range& rng, adaptor_without_object<Predicate>)
    {
        return oven::make_filter_range<Predicate>(rng);
    }

    template< class Predicate, class Range > inline
    const filter_range<Predicate, typename boost::add_const<Range>::type>
    operator|(const Range& rng, adaptor_without_object<Predicate>)
    {
        return oven::make_filter_range<Predicate>(rng);
    }


} // namespace filter_range_detail


template< class Predicate > inline
filter_range_detail::adaptor<Predicate>
filtered(Predicate pred)
{
    return filter_range_detail::adaptor<Predicate>(pred);
}


// without object
template< class Predicate > inline
filter_range_detail::adaptor_without_object<Predicate>
filtered()
{
    return filter_range_detail::adaptor_without_object<Predicate>();
}


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::filter_range, 2)


#endif
