#ifndef PSTADE_OVEN_CHECK_RANGE_HPP
#define PSTADE_OVEN_CHECK_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./check_iterator.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace check_range_detail {


    template< class Range >
    struct super_ :
        iter_range<
            check_iterator<
                typename range_iterator<Range>::type
            >
        >
    { };


} // namespace check_range_detail


template< class Range >
struct check_range :
    check_range_detail::super_<Range>::type,
    private as_lightweight_proxy< check_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
    typedef check_range type;

private:
    typedef typename check_range_detail::super_<Range>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit check_range(Range& rng) :
        super_t(
            iter_t(boost::begin(rng), boost::begin(rng), boost::end(rng)),
            iter_t(boost::end(rng),   boost::begin(rng), boost::end(rng))
        )
    { }

    typedef Range pstade_oven_range_base_type;
};


PSTADE_OBJECT_GENERATOR(make_check_range,
    (check_range< deduce_to_qualified<from_1> >) const)
PSTADE_PIPABLE(checked, (op_make_check_range))


} } // namespace pstade::oven


#endif
