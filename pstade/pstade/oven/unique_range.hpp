#ifndef PSTADE_OVEN_UNIQUE_RANGE_HPP
#define PSTADE_OVEN_UNIQUE_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/egg/function.hpp>
#include "./detail/equal_to.hpp"
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./unique_iterator.hpp"


namespace pstade { namespace oven {


namespace unique_range_detail {


    template< class ForwardRange, class BinaryPred >
    struct super_
    {
        typedef boost::iterator_range<
            unique_iterator<
                typename boost::range_result_iterator<ForwardRange>::type,
                BinaryPred
            >
        > type;
    };


} // namespace tab_expand_range_detail


template< class ForwardRange, class BinaryPred = detail::equal_to >
struct unique_range :
    unique_range_detail::super_<ForwardRange, BinaryPred>::type
{
private:
    typedef typename unique_range_detail::super_<ForwardRange, BinaryPred>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit unique_range(ForwardRange& rng, BinaryPred pred = detail::equal_to()) :
        super_t(
            iter_t(boost::begin(rng), boost::begin(rng), boost::end(rng), pred),
            iter_t(boost::end(rng), boost::begin(rng), boost::end(rng), pred)
        )
    { }
};


namespace unique_range_detail {


    struct baby_generator
    {
        template< class ForwardRange, class BinaryPred = detail::equal_to >
        struct apply
        {
            typedef typename boost::remove_cv<BinaryPred>::type pred_t;
            typedef const unique_range<ForwardRange, pred_t> type;
        };

        template< class Result, class ForwardRange, class BinaryPred >
        Result call(ForwardRange& rng, BinaryPred pred)
        {
            return Result(rng, pred);
        }

        template< class Result, class ForwardRange >
        Result call(ForwardRange& rng)
        {
            return Result(rng);
        }
    };


} // namespace unique_range_detail


PSTADE_EGG_FUNCTION(make_unique_range, unique_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(uniqued, unique_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::unique_range, 2)


#endif
