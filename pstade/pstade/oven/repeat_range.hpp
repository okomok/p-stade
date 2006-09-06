#ifndef PSTADE_OVEN_REPEAT_RANGE_HPP
#define PSTADE_OVEN_REPEAT_RANGE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t
#include <boost/range/iterator_range.hpp>
#include <pstade/remove_cvr.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include "./as_lightweight_proxy.hpp"
#include "./detail/concept_check.hpp"
#include "./range_iterator.hpp"
#include "./repeat_iterator.hpp"
#include "./sub_range_result.hpp"


namespace pstade { namespace oven {


namespace repeat_range_detail {


    template< class ForwardRange, class Size >
    struct super_
    {
        typedef boost::iterator_range<
            repeat_iterator<
                typename range_iterator<ForwardRange>::type,
                Size
            >
        > type;
    };


} // namespace repeat_range_detail


template< class ForwardRange, class Size = std::size_t >
struct repeat_range :
    repeat_range_detail::super_<ForwardRange, Size>::type,
    private as_lightweight_proxy< repeat_range<ForwardRange, Size> >
{
    typedef ForwardRange pstade_oven_range_base_type;

private:
    PSTADE_OVEN_DETAIL_REQUIRES(ForwardRange, ForwardRangeConcept);
    typedef typename repeat_range_detail::super_<ForwardRange, Size>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    repeat_range(ForwardRange& rng, Size sz) :
        super_t(
            iter_t(boost::begin(rng), 0,  boost::begin(rng), boost::end(rng)),
            iter_t(boost::begin(rng), sz, boost::begin(rng), boost::end(rng))
        )
    { }

    typename sub_range_result<ForwardRange>::type source() const
    {
        return boost::make_iterator_range(this->begin().sbegin(), this->begin().send());
    }
};


namespace repeat_range_detail {


    struct baby_generator
    {
        template< class Unused, class ForwardRange, class Size >
        struct result
        {
            typedef typename remove_cvr<Size>::type sz_t;
            typedef repeat_range<ForwardRange, sz_t> const type;
        };

        template< class Result, class ForwardRange, class Size >
        Result call(ForwardRange& rng, Size sz)
        {
            return Result(rng, sz);
        }
    };


} // namespace repeat_range_detail


PSTADE_EGG_FUNCTION(make_repeat_range, repeat_range_detail::baby_generator)
PSTADE_EGG_PIPABLE(repeated, repeat_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
