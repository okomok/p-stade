#ifndef PSTADE_OVEN_POP_RANGE_HPP
#define PSTADE_OVEN_POP_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Question:
//
// 'rng|applied(pop);' is better?
// But Haskell provides one named 'init' as primitive.


#include <boost/range/begin.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/range_prior.hpp"
#include "./concepts.hpp"
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


template< class Range >
struct pop_range :
    sub_range_base<Range>::type,
    private as_lightweight_proxy< pop_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((Forward<Range>));

private:
    typedef typename sub_range_base<Range>::type super_t;

public:
    explicit pop_range(Range& rng) :
        super_t(boost::begin(rng), detail::range_prior(rng))
    { }

    typedef Range pstade_oven_range_base_type;
};


PSTADE_OBJECT_GENERATOR(make_pop_range, const pop_range, (by_qualified), ~)
PSTADE_PIPABLE(popped, op_make_pop_range)


} } // namespace pstade::oven


#endif
