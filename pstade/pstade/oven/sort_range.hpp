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
#include "./direct_range.hpp"
#include "./indirect_range.hpp"
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./share_range.hpp"


namespace pstade { namespace oven {


namespace sort_range_detail {


    template< class Range >
    struct iterator_container
    {   
        typedef typename boost::range_result_iterator<Range>::type iter_t;
        typedef std::vector<iter_t> type;
    };


    template< class Range, class BinaryPred >
    struct share_range_initializer
    {
        typedef typename iterator_container<Range>::type iters_t;

        explicit share_range_initializer(Range& rng, BinaryPred pred)
        {
            std::auto_ptr<iters_t> piters(new iters_t());
            oven::copy(rng|oven::directed, garlic::back_inserter(*piters));
            std::sort(boost::begin(*piters), boost::end(*piters), boost::make_indirect_fun(pred));
            m_iters = oven::share_range<iters_t>(piters.release());
        }

    protected:
         oven::share_range<iters_t> m_iters;
    };


    template< class Range >
    struct super_
    {
        typedef oven::indirect_range<
            oven::share_range<
                typename iterator_container<Range>::type
            >
        > type;
    };


    struct less_than
    {
        typedef bool result_type;

        template< class X, class Y >
        bool operator()(const X& x, const Y& y) const
        {
            return x < y;
        }
    };


} // namespace sort_range_detail


template< class Range, class BinaryPred = sort_range_detail::less_than >
struct sort_range :
    private sort_range_detail::share_range_initializer<Range, BinaryPred>,
    sort_range_detail::super_<Range>::type
{
private:
    typedef sort_range_detail::share_range_initializer<Range, BinaryPred> sh_rng_bt;
    typedef typename sort_range_detail::super_<Range>::type super_t;

public:
    explicit sort_range(Range& rng, BinaryPred pred = sort_range_detail::less_than()) :
        sh_rng_bt(rng, pred),
        super_t(sh_rng_bt::m_iters)
    { }
};


namespace sort_range_detail {


    struct baby_generator
    {
        template< class Range, class BinaryPred = less_than >
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
