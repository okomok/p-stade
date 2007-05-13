#ifndef PSTADE_OVEN_SHARED_LVALUE_RANGE_HPP
#define PSTADE_OVEN_SHARED_LVALUE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./shared_lvalue_iterator.hpp"


namespace pstade { namespace oven {


namespace shared_lvalue_range_detail {


    template< class Range >
    struct super_ :
        iter_range<
            shared_lvalue_iterator<
                typename range_iterator<Range>::type
            >
        >
    { };


} // namespace shared_lvalue_range_detail


template< class Range >
struct shared_lvalue_range :
    shared_lvalue_range_detail::super_<Range>::type,
    private as_lightweight_proxy< shared_lvalue_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

private:
    typedef typename shared_lvalue_range_detail::super_<Range>::type super_t;

public:
    explicit shared_lvalue_range(Range& rng) :
        super_t(rng)
    { }

    typedef Range pstade_oven_range_base_type;
};


namespace shared_lvalue_range_detail {


    struct baby_make
    {
        template< class Myself, class Range >
        struct apply
        {
            typedef shared_lvalue_range<Range> const type;
        };

        template< class Result, class Range >
        Result call(Range& rng)
        {
            return Result(rng);
        }
    };


} // namespace shared_lvalue_range_detail


PSTADE_EGG_FUNCTION(make_shared_lvalue_range, shared_lvalue_range_detail::baby_make)
PSTADE_EGG_PIPABLE(shared_lvalues, shared_lvalue_range_detail::baby_make)


} } // namespace pstade::oven


#endif
