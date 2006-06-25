#ifndef PSTADE_OVEN_ZIP_RANGE_HPP
#define PSTADE_OVEN_ZIP_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/zip_iterator.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include "./is_lightweight_proxy.hpp"


namespace pstade { namespace oven {


namespace zip_range_detail {


    using boost::detail::tuple_impl_specific::tuple_meta_transform;
    using boost::detail::tuple_impl_specific::tuple_transform;


    struct meta_result
    {
        template< class RangeRef >
        struct apply :
            boost::range_result_iterator<
                typename boost::remove_reference<RangeRef>::type
            >
        {
            BOOST_MPL_ASSERT(( boost::is_reference<RangeRef> ));
        };
    };


    struct begin_fun : meta_result
    {
        template< class Range >
        typename apply<Range&>::type
        operator()(Range& rng) const
        {
            return boost::begin(rng);
        }
    };


    struct end_fun : meta_result
    {
        template< class Range >
        typename apply<Range&>::type
        operator()(Range& rng) const
        {
            return boost::end(rng);
        }
    };


    template< class RangeRefTuple >
    struct super_
    {
        typedef boost::iterator_range<
            boost::zip_iterator<
                typename tuple_meta_transform<
                    RangeRefTuple, meta_result
                >::type
            >
        > type;
    };


} // namespace zip_range_detail


template< class RangeRefTuple >
struct zip_range :
    zip_range_detail::super_<RangeRefTuple>::type
{
private:
    typedef typename zip_range_detail::super_<RangeRefTuple>::type super_t;
    typedef typename super_t::iterator iter_t;

public:
    explicit zip_range(const RangeRefTuple& rngs) :
        super_t(
            iter_t(zip_range_detail::tuple_transform(rngs, zip_range_detail::begin_fun())),
            iter_t(zip_range_detail::tuple_transform(rngs, zip_range_detail::end_fun()))
        )
    { }
};


template< class RangeRefTuple > inline const
zip_range<RangeRefTuple>
make_zip_range(const RangeRefTuple& rngs)
{
    return zip_range<RangeRefTuple>(rngs);
}


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::zip_range, 1)


#endif
