#ifndef PSTADE_OVEN_CLEAR_RANGE_HPP
#define PSTADE_OVEN_CLEAR_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/end.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


template< class Range >
struct clear_range :
    sub_range_base<Range>::type,
    private as_lightweight_proxy< clear_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
    typedef clear_range type;

private:
    typedef typename sub_range_base<Range>::type super_t;

public:
    explicit clear_range(Range& rng) :
        super_t(boost::end(rng), boost::end(rng))
    { }

    typedef Range pstade_oven_range_base_type;
};


PSTADE_OBJECT_GENERATOR(make_clear_range,
    (clear_range< deduce_to_qualified<from_1> >) const)
PSTADE_PIPABLE(cleared, (op_make_clear_range))


} } // namespace pstade::oven


#endif
