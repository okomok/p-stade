#ifndef PSTADE_OVEN_ADJACENT_TRANSFORM_RANGE_HPP
#define PSTADE_OVEN_ADJACENT_TRANSFORM_RANGE_HPP


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
#include "./adjacent_transform_iterator.hpp"


namespace pstade { namespace oven {


namespace adjacent_transform_range_detail {


    template< class ForwardRange, class Functor, class BinaryPred >
    struct super_
    {
        typedef boost::iterator_range<
            adjacent_transform_iterator<
                typename boost::range_result_iterator<ForwardRange>::type,
                Functor, BinaryPred
            >
        > type;
    };


} // namespace adjacent_transform_range_detail


template< class ForwardRange, class Functor, class BinaryPred = detail::equal_to >
struct adjacent_transform_range :
    adjacent_transform_range_detail::super_<ForwardRange, Functor, BinaryPred>::type
{
private:
    typedef typename adjacent_transform_range_detail::super_<ForwardRange, Functor, BinaryPred>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit adjacent_transform_range(ForwardRange& rng, Functor fun, BinaryPred pred = detail::equal_to()) :
        super_t(
            iter_t(boost::begin(rng), boost::begin(rng), boost::end(rng), fun, pred),
            iter_t(boost::end(rng), boost::begin(rng), boost::end(rng), fun, pred)
        )
    { }
};


namespace adjacent_transform_range_detail {


    struct baby_generator
    {
        template< class ForwardRange, class Functor, class BinaryPred = detail::equal_to >
        struct result
        {
			typedef typename boost::remove_cv<Functor>::type fun_t;
            typedef typename boost::remove_cv<BinaryPred>::type pred_t;
            typedef const adjacent_transform_range<ForwardRange, fun_t, pred_t> type;
        };

        template< class Result, class ForwardRange, class Functor, class BinaryPred >
        Result call(ForwardRange& rng, Functor fun, BinaryPred pred)
        {
            return Result(rng, fun, pred);
        }

        template< class Result, class ForwardRange, class Functor >
        Result call(ForwardRange& rng, Functor fun)
        {
            return Result(rng, fun);
        }
    };


} // namespace adjacent_transform_range_detail


PSTADE_EGG_FUNCTION(make_adjacent_transform_range, adjacent_transform_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(adjacent_transformed, adjacent_transform_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::adjacent_transform_range, 3)


#endif
