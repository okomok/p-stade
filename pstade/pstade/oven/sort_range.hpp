#ifndef PSTADE_OVEN_SORT_RANGE_HPP
#define PSTADE_OVEN_SORT_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Rejected...
//
// Because this adaptor is *expensive* enough
// to effect on your software design sooner or later.
// On the other hand, when you can accept the big time-and-space,
// this may be still useful. So I don't remove...


#include <boost/ptr_container/indirect_fun.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/functional.hpp> // less
#include <pstade/pass_by.hpp>
#include "./algorithm.hpp" // sort
#include "./as_lightweight_proxy.hpp"
#include "./concepts.hpp"
#include "./out_place_range.hpp"


namespace pstade { namespace oven {


namespace sort_range_detail {


    template< class Compare >
    struct sort_fun
    {
        explicit sort_fun(Compare const& comp) :
            m_comp(comp)
        { }

        template< class Range >
        void operator()(Range& its) const
        {
            oven::sort(its, boost::make_indirect_fun(m_comp));
        }

    private:
        Compare m_comp;
    };


    template<
        class Range,
        class Compare
    >
    struct super_
    {
        typedef out_place_range<
            Range, sort_fun<Compare>
        > type;
    };


} // namespace sort_range_detail


template<
    class Range,
    class Compare = less_fun
>
struct sort_range :
    sort_range_detail::super_<Range, Compare>::type,
    private as_lightweight_proxy< sort_range<Range, Compare> >
{
    PSTADE_CONCEPT_ASSERT((Forward<Range>));
    // PSTADE_CONCEPT_ASSERT((Readable<Range>));
    typedef Compare compare_type;

private:
    typedef typename sort_range_detail::super_<Range, Compare>::type super_t;
    typedef typename super_t::function_type fun_t;

public:
    explicit sort_range(Range& rng, Compare const& comp = pstade::less) :
        super_t(rng, fun_t(comp))
    { }
};


namespace sort_range_detail {


    struct baby_make
    {
        template< class Myself, class Range, class Compare = less_fun >
        struct apply
        {
            typedef typename pass_by_value<Compare>::type comp_t;
            typedef sort_range<Range, comp_t> const type;
        };

        template< class Result, class Range, class Compare >
        Result call(Range& rng, Compare& comp)
        {
            return Result(rng, comp);
        }

        template< class Result, class Range >
        Result call(Range& rng)
        {
            return Result(rng);
        }
    };


} // namespace sort_range_detail


PSTADE_EGG_FUNCTION(make_sort_range, sort_range_detail::baby_make)
PSTADE_EGG_PIPABLE(sorted, sort_range_detail::baby_make)


} } // namespace pstade::oven


#endif
