#ifndef PSTADE_OVEN_SCAN_RANGE_HPP
#define PSTADE_OVEN_SCAN_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <pstade/functional.hpp> // plus
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./scan_iterator.hpp"


namespace pstade { namespace oven {


namespace scan_range_detail {


    template<
        class Range,
        class State,
        class BinaryFun
    >
    struct super_ :
        iter_range<
            scan_iterator<
                typename range_iterator<Range>::type,
                State,
                BinaryFun
            >
        >
    { };


} // namespace scan_range_detail


template<
    class Range,
    class State,
    class BinaryFun = op_plus
>
struct scan_range :
    scan_range_detail::super_<Range, State, BinaryFun>::type,
    private as_lightweight_proxy< scan_range<Range, State, BinaryFun> >
{
    PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
    // PSTADE_CONCEPT_ASSERT((Readable<Range>));
    typedef State state_type;
    typedef BinaryFun function_type;

private:
    typedef typename scan_range_detail::super_<Range, State, BinaryFun>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    scan_range(Range& rng, State const& init, BinaryFun const& fun = pstade::plus) :
        super_t(
            iter_t(boost::begin(rng), init, fun),
            iter_t(boost::end(rng),   init, fun)
        )
    { }

    function_type const& function() const
    {
        return this->begin().function();
    }

    typedef Range pstade_oven_range_base_type;
};


PSTADE_OBJECT_GENERATOR_WITH_DEFAULTS(make_scan_range, const scan_range,
    (by_qualified)(by_value)(by_value), (argument_needed)(argument_needed)(op_plus))
PSTADE_PIPABLE(scanned, op_make_scan_range)


} } // namespace pstade::oven


#endif
