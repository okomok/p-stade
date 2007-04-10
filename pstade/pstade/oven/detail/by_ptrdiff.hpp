#ifndef PSTADE_OVEN_DETAIL_BY_PTRDIFF_HPP
#define PSTADE_OVEN_DETAIL_BY_PTRDIFF_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Used with "../before_stable_partition.hpp".


#include <cstddef> // ptrdiff_t
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/function.hpp>
#include <pstade/pipable.hpp>
#include <pstade/value_cast.hpp>
#include "../iter_range.hpp"
#include "../range_iterator.hpp"


namespace pstade { namespace oven { namespace detail {


template< class Iterator >
struct ptrdiff_iterator;


template< class Iterator >
struct ptrdiff_iterator_super
{
    typedef
        boost::iterator_adaptor<
            ptrdiff_iterator<Iterator>,
            Iterator,
            boost::use_default,
            boost::use_default,
            boost::use_default,
            std::ptrdiff_t
        >
    type;
};


template< class Iterator >
struct ptrdiff_iterator :
    ptrdiff_iterator_super<Iterator>::type
{
private:
    typedef typename ptrdiff_iterator_super<Iterator>::type super_t;
    typedef typename super_t::difference_type diff_t;

public:
    explicit ptrdiff_iterator()
    { }

    explicit ptrdiff_iterator(Iterator const& it) :
        super_t(it)
    { }

    template< class I >
    ptrdiff_iterator(ptrdiff_iterator<I> const& other,
        typename boost::enable_if_convertible<I, Iterator>::type * = 0
    ) :
        super_t(other.base())
    { }

friend class boost::iterator_core_access;
    template< class I >
    diff_t distance_to(ptrdiff_iterator<I> const& other) const
    {
        return pstade::value_cast<diff_t>(other.base() - this->base());
    }
};


template< class Range >
struct baby_by_ptrdiff
{
    typedef
        ptrdiff_iterator<
            typename range_iterator<Range>::type
        >
    iter_t;

    typedef
        iter_range<iter_t> const
    result_type;

    result_type operator()(Range& rng) const
    {
        return result_type(boost::begin(rng), boost::end(rng));
    }
};


PSTADE_FUNCTION(make_by_ptrdiff, (baby_by_ptrdiff<_>))
PSTADE_PIPABLE(by_ptrdiff, (op_make_by_ptrdiff))


} } } // namespace pstade::oven::detail


#endif
