#ifndef PSTADE_OVEN_OUT_PLACE_RANGE_HPP
#define PSTADE_OVEN_OUT_PLACE_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Rejected...
//
// See "./sort_range.hpp"


// Note:
//
// Iterators manage temporary container for BOOST_FOREACH.


#include <memory> // auto_ptr
#include <vector>
#include <pstade/new.hpp>
#include <pstade/object_generator.hpp>
#include <pstade/pipable.hpp>
#include <pstade/unused.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./copy_range.hpp"
#include "./concepts.hpp"
#include "./direct_range.hpp"
#include "./indirect_range.hpp"
#include "./range_iterator.hpp"
#include "./share_range.hpp"


namespace pstade { namespace oven {


namespace out_place_range_detail {


    template< class Range >
    struct iter_sequence
    {   
        typedef typename range_iterator<Range>::type iter_t;
        typedef std::vector<iter_t> type;
    };


    template< class Range >
    struct super_
    {
        typedef oven::indirect_range<
            oven::share_range<
                typename iter_sequence<Range>::type
            > const
        > type;
    };


    template< class IterSeq, class Range, class UnaryFun >
    oven::share_range<IterSeq> const
    make_share(Range& rng, UnaryFun fun)
    {
        // Note:
        // 'share_range' size never be affected by its holding sequence
        // once constructed. So, first of all, you must initialize the sequence
        // before passing it to 'share_range'.
        std::auto_ptr<IterSeq> pseq(pstade::new_<IterSeq>());
        *pseq = oven::copy_range<IterSeq>(rng|directed);

        // Question:
        // What should be passed to 'fun'?
        fun(*pseq);        

        return share_range<IterSeq>(pseq.release());
    }


} // namespace out_place_range_detail


template<
    class Range,
    class UnaryFun = op_unused
>
struct out_place_range :
    out_place_range_detail::super_<Range>::type,
    private as_lightweight_proxy< out_place_range<Range, UnaryFun> >
{
    PSTADE_CONCEPT_ASSERT((Forward<Range>));
    typedef UnaryFun function_type;

private:
    typedef typename out_place_range_detail::super_<Range>::type super_t;
    typedef typename out_place_range_detail::iter_sequence<Range>::type seq_t;

public:
    explicit out_place_range(Range& rng, UnaryFun const& fun = unused) :
        super_t(out_place_range_detail::make_share<seq_t>(rng, fun))
    { }

    typedef Range pstade_oven_range_base_type;
};


PSTADE_OBJECT_GENERATOR_WITH_DEFAULTS(make_out_place_range, const out_place_range,
    (by_qualified)(by_value), (argument_needed)(op_unused))
PSTADE_PIPABLE(out_placed, op_make_out_place_range)


} } // namespace pstade::oven


#endif
