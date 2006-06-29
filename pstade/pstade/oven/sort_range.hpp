#ifndef PSTADE_OVEN_SORT_RANGE_HPP
#define PSTADE_OVEN_SORT_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// iterators manage temporary container for BOOST_FOREACH.


#include <algorithm> // copy, sort
#include <memory> // auto_ptr
#include <vector>
#include <boost/ptr_container/indirect_fun.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/garlic/back_inserter.hpp>
#include "./copy.hpp"
#include "./detail/less_than.hpp"
#include "./direct_range.hpp"
#include "./indirect_range.hpp"
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./share_range.hpp"


namespace pstade { namespace oven {


namespace sort_range_detail {


    template< class Range >
    struct iter_sequence
    {   
        typedef typename boost::range_result_iterator<Range>::type iter_t;
        typedef std::vector<iter_t> type;
    };


    template< class Range >
    struct super_
    {
        typedef oven::indirect_range< const
            oven::share_range<
                typename iter_sequence<Range>::type
            >
        > type;
    };


    template< class Sequence, class Range, class BinaryPred > const
    oven::share_range<Sequence> make_share(Range& rng, BinaryPred pred)
    {
        std::auto_ptr<Sequence> pseq(new Sequence()); {
            oven::copy(rng|oven::directed, garlic::back_inserter(*pseq));
            std::sort(boost::begin(*pseq), boost::end(*pseq), boost::make_indirect_fun(pred));
        }

        return share_range<Sequence>(pseq.release());
    }

} // namespace sort_range_detail


template< class Range, class BinaryPred = detail::less_than_fun >
struct sort_range :
    sort_range_detail::super_<Range>::type
{
private:
    typedef typename sort_range_detail::super_<Range>::type super_t;
    typedef typename sort_range_detail::iter_sequence<Range>::type seq_t;

public:
    explicit sort_range(Range& rng, BinaryPred pred = detail::less_than) :
        super_t(sort_range_detail::make_share<seq_t>(rng, pred))
    { }
};


namespace sort_range_detail {


    struct baby_generator
    {
        template< class Range, class BinaryPred = detail::less_than_fun >
        struct result
        {
            typedef typename boost::remove_cv<BinaryPred>::type pred_t;
            typedef const sort_range<Range, pred_t> type;
        };

        template< class Result, class Range, class BinaryPred >
        Result call(Range& rng, BinaryPred pred)
        {
            return Result(rng, pred);
        }

        template< class Result, class Range >
        Result call(Range& rng)
        {
            return Result(rng);
        }
    };


} // namespace sort_range_detail


PSTADE_EGG_FUNCTION(make_sort_range, sort_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(sorted, sort_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::sort_range, 2)


#endif
