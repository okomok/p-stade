#ifndef PSTADE_OVEN_IDENTITY_RANGE_HPP
#define PSTADE_OVEN_IDENTITY_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pass_by.hpp>
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

private:
    typedef typename identity_range_detail::super_<Range, Traversal>::type super_t;

public:
    explicit identity_range(Range& rng) :
        super_t(rng)
    { }

    typedef Range pstade_oven_range_base_type;
};


struct op_make_identity_range :
    callable<op_make_identity_range>
{
    template< class Myself, class Range, class Traversal = boost::use_default >
    struct apply
    {
        typedef typename pass_by_value<Traversal>::type trv_t;
        typedef identity_range<Range, trv_t> const type;
    };

    template< class Result, class Range, class Traversal >
    Result call(Range& rng, Traversal) const
    {
        return Result(rng);
    }

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        return Result(rng);
    }
};


PSTADE_CONSTANT(make_identity_range, op_make_identity_range)
PSTADE_PIPABLE(identities, op_make_identity_range)


} } // namespace pstade::oven


#endif
