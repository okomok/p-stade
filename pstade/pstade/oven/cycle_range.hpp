#ifndef PSTADE_OVEN_CYCLE_RANGE_HPP
#define PSTADE_OVEN_CYCLE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./cycle_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./sub_range_base.hpp"


namespace pstade { namespace oven {


namespace cycle_range_detail {


    template<
        class Range,
        class Size
    >
    struct super_ :
        iter_range<
            cycle_iterator<
                typename range_iterator<Range>::type,
                Size
            >
        >
    { };


} // namespace cycle_range_detail


template<
    class Range,
    class Size = std::size_t
>
struct cycle_range :
    cycle_range_detail::super_<Range, Size>::type,
    private as_lightweight_proxy< cycle_range<Range, Size> >
{
    PSTADE_CONCEPT_ASSERT((Forward<Range>));
    typedef cycle_range type;
    typedef typename sub_range_base<Range>::type source_type;

private:
    typedef typename cycle_range_detail::super_<Range, Size>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    cycle_range(Range& rng, Size sz) :
        super_t(
            iter_t(boost::begin(rng), 0,  boost::begin(rng), boost::end(rng)),
            iter_t(boost::begin(rng), sz, boost::begin(rng), boost::end(rng))
        )
    { }

    source_type const source() const
    {
        return source_type(this->begin().sbegin(), this->begin().send());
    }

    typedef Range pstade_oven_range_base_type;
};


PSTADE_OBJECT_GENERATOR(make_cycle_range,
    (cycle_range< deduce_to_qualified<from_1>, deduce_to_value<from_2> >) const)
PSTADE_PIPABLE(cycled, (op_make_cycle_range))


} } // namespace pstade::oven


#endif
