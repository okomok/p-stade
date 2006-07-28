#ifndef PSTADE_OVEN_SHARE_RANGE_HPP
#define PSTADE_OVEN_SHARE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <pstade/egg/function.hpp>
#include "./detail/concept_check.hpp"
#include "./lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./share_iterator.hpp"


namespace pstade { namespace oven {


namespace share_range_detail {


    template< class Range >
    struct super_
    {
        typedef boost::iterator_range<
            share_iterator<Range>
        > type;
    };


    template< class Range >
    typename super_<Range>::type make_super(Range *prng)
    {
        boost::shared_ptr<Range> sprng(prng);
        return boost::make_iterator_range(
            oven::make_share_iterator(boost::begin(*sprng), sprng),
            oven::make_share_iterator(boost::end(*sprng), sprng)
        );
    }


} // namespace share_range_detail


template< class Range >
struct share_range :
    share_range_detail::super_<Range>::type,
    private lightweight_proxy< share_range<Range> >
{
private:
    PSTADE_OVEN_DETAIL_REQUIRES(Range, SinglePassRangeConcept);
    typedef typename share_range_detail::super_<Range>::type super_t;

public:
    explicit share_range(Range *prng) :
        super_t(share_range_detail::make_super(prng))
    { }

    Range& operator*() const
    { return boost::begin(*this).range(); }
};


namespace share_range_detail {


    struct baby_generator
    {
        template< class Unused, class RangePtrT >
        struct result
        {
            typedef typename boost::remove_pointer<RangePtrT>::type rng_t;
            typedef share_range<rng_t> const type;
        };

        template< class Result, class RangePtrT >
        Result call(RangePtrT prng)
        {
            return Result(prng);
        }
    };


} // namespace share_range_detail


PSTADE_EGG_FUNCTION(make_share_range, share_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(shared, share_range_detail::baby_generator)


} } // namespace pstade::oven


#endif
