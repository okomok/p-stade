#ifndef PSTADE_OVEN_ITER_RANGE_HPP
#define PSTADE_OVEN_ITER_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Non-Assignable version of 'boost::iterator_range'.
// Note that 'operator==' is different from that.


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/utility/enable_if.hpp>
#include <pstade/nonassignable.hpp>
#include "./extension.hpp"


namespace pstade { namespace oven {


template< class Iterator >
struct iter_range :
    private as_lightweight_proxy< iter_range<Iterator> >,
    private nonassignable
{
    template< class Iterator >
    iter_range(Iterator const& first, Iterator const& last) :
        m_first(first), m_last(last)
    { }

    template< class Range >
    iter_range(Range& rng,
        // See <pstade/egg/detail/disable_if_same.hpp>.
        boost::disable_if< boost::is_same<Range, iter_range> >::type * = 0
    ) :
        m_first(boost::begin(rng)), m_last(boost::end(rng))
    { }

    template< class Range >
    iter_range(Range const& rng) :
        m_first(boost::begin(rng)), m_last(boost::end(rng))
    { }

// private:
    Iterator const& detail_begin() const
    {
        return m_first;
    }

    Iterator const& detail_end() const
    {
        return m_last;
    }

private:
    Iterator const m_first, m_last;
};


namespace pstade_oven_extension {


    template< class Iterator >
    struct Range< pstade::oven::iter_range<Iterator> >
    {
        template< class X >
        struct associate
        {
            typedef Iterator mutable_iterator;
            typedef Iterator constant_iterator;
        };

        template< class Iterator, class X >
        Iterator begin(X& x)
        {
            return x.detail_begin();
        }

        template< class Iterator, class X >
        Iterator end(X& x)
        {
            return x.detail_end();
        }
    };


} // namespace pstade_oven_extension


PSTADE_OVEN_EXTENSION_TEMPLATE((pstade)(oven)(iter_range), 1)


} } // namespace pstade::oven


#endif
