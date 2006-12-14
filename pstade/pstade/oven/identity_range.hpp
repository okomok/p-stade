#ifndef PSTADE_OVEN_IDENTITY_RANGE_HPP
#define PSTADE_OVEN_IDENTITY_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./identity_iterator.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace identity_range_detail {


    template<
        class Range,
        class Traversal
    >
    struct super_ :
        iter_range<
            identity_iterator<
                typename range_iterator<Range>::type,
                Traversal
            >
        >
    { };


} // namespace identity_range_detail


template<
    class Range,
    class Traversal = boost::use_default
>
struct identity_range :
    identity_range_detail::super_<Range, Traversal>::type,
    private as_lightweight_proxy< identity_range<Range, Traversal> >
{
    PSTADE_CONCEPT_ASSERT((SinglePass<Range>));
    typedef identity_range type;

private:
    typedef typename identity_range_detail::super_<Range, Traversal>::type super_t;

public:
    explicit identity_range(Range& rng, unused_argument = unused_argument()) :
        super_t(rng)
    { }

    typedef Range pstade_oven_range_base_type;
};


PSTADE_OBJECT_GENERATOR(make_identity_range,
    (identity_range< deduce_to_qualified<from_1>, deduce_to_value<from_2, boost::use_default> >) const)
PSTADE_PIPABLE(identities, (op_make_identity_range))


} } // namespace pstade::oven


#endif
