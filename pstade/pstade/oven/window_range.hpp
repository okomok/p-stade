#ifndef PSTADE_OVEN_WINDOW_RANGE_HPP
#define PSTADE_OVEN_WINDOW_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./detail/next_prior.hpp" // next
#include "./distance.hpp"
#include "./range_iterator.hpp"
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


namespace window_range_detail {


    template< class Super, class Range, class Difference >
    Super make(Range& rng, Difference n, Difference m)
    {
        // Should a "bigger" window be allowed?
        // BOOST_ASSERT(0 <= n && n <= m && m <= oven::distance(rng));

        typedef typename range_iterator<Range>::type iter_t;
        iter_t first = detail::next(boost::begin(rng), n);
        return Super(first, detail::next(first, m - n));
    }


} // namespace window_range_detail


template< class Range >
struct window_range :
    sub_range_base<Range>::type,
    private as_lightweight_proxy< window_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((Forward<Range>));
    typedef window_range type;

private:
    typedef typename sub_range_base<Range>::type super_t;

public:
    template< class Difference >
    window_range(Range& rng, Difference n, Difference m) :
        super_t(window_range_detail::make<super_t>(rng, n, m))
    { }

    typedef Range pstade_oven_range_base_type;
};


PSTADE_OBJECT_GENERATOR(make_window_range,
    (window_range< deduce_to_qualified<from_1> >) const)
PSTADE_PIPABLE(through_window, (op_make_window_range))


} } // namespace pstade::oven


#endif
