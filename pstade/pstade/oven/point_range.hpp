#ifndef PSTADE_OVEN_POINT_RANGE_HPP
#define PSTADE_OVEN_POINT_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Makes Pointer Range from std::vector.


#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/nullptr.hpp>
#include <pstade/oven/distance.hpp>
#include "./detail/concept_check.hpp"
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"
#include "./range_pointer.hpp"


namespace pstade { namespace oven {


namespace point_range_detail {


    template< class ContiguousRange >
    struct super_
    {
        typedef boost::iterator_range<
            typename range_pointer<ContiguousRange>::type
        > type;
    };


    template< class ContiguousRange >
    typename super_<ContiguousRange>::type
    make_super(ContiguousRange& vec)
    {
        typedef typename super_<ContiguousRange>::type super_t;
        typedef typename super_t::iterator iter_t;
        BOOST_STATIC_ASSERT( boost::is_pointer<iter_t>::value );

        if (boost::empty(vec))
            return super_t(iter_t(PSTADE_NULLPTR), iter_t(PSTADE_NULLPTR));

        return super_t(
            boost::addressof( *boost::begin(vec) ),
            boost::addressof( *boost::begin(vec) ) + oven::distance(vec)
        );
    }


} // namespace point_range_detail


template< class ContiguousRange >
struct point_range :
    point_range_detail::super_<ContiguousRange>::type
{
private:
    PSTADE_OVEN_DETAIL_REQUIRES(ContiguousRange, RandomAccessRangeConcept);
    typedef typename point_range_detail::super_<ContiguousRange>::type super_t;

public:
    explicit point_range(ContiguousRange& vec) :
        super_t(point_range_detail::make_super(vec))
    { }
};


namespace point_range_detail {


    struct baby_generator
    {
        template< class Unused, class ContiguousRange >
        struct result
        {
            typedef point_range<ContiguousRange> const type;
        };

        template< class Result, class ContiguousRange >
        Result call(ContiguousRange& rng)
        {
            return Result(rng);
        }
    };


} // namespace point_range_detail



PSTADE_EGG_FUNCTION(make_point_range, point_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(pointed, point_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::point_range, 1)


#endif
