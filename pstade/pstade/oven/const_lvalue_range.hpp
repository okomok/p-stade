#ifndef PSTADE_OVEN_CONST_LVALUE_RANGE_HPP
#define PSTADE_OVEN_CONST_LVALUE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/iterator_range.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./const_lvalue_iterator.hpp"
#include "./concepts.hpp"
#include "./range_iterator.hpp"


namespace pstade { namespace oven {


namespace const_lvalue_range_detail {


    template< class Range >
    struct super_
    {
        typedef boost::iterator_range<
            const_lvalue_iterator<
                typename range_iterator<Range>::type
            >
        > type;
    };


} // namespace const_lvalue_range_detail


template< class Range >
struct const_lvalue_range :
    const_lvalue_range_detail::super_<Range>::type,
    private as_lightweight_proxy< const_lvalue_range<Range> >
{
    PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

private:
    typedef typename const_lvalue_range_detail::super_<Range>::type super_t;

public:
    explicit const_lvalue_range(Range& rng) :
        super_t(rng)
    { }

    typedef Range pstade_oven_range_base_type;
};


namespace const_lvalue_range_detail {


    struct baby_make
    {
        template< class Myself, class Range >
        struct apply
        {
            typedef const_lvalue_range<Range> const type;
        };

        template< class Result, class Range >
        Result call(Range& rng)
        {
            return Result(rng);
        }
    };


} // namespace const_lvalue_range_detail


PSTADE_EGG_FUNCTION(make_const_lvalue_range, const_lvalue_range_detail::baby_make)
PSTADE_EGG_PIPABLE(const_lvalues, const_lvalue_range_detail::baby_make)


} } // namespace pstade::oven


#endif
