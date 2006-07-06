#ifndef PSTADE_OVEN_POINTER_RANGE_HPP
#define PSTADE_OVEN_POINTER_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// make Pointer Range from std::vector.


#include <boost/iterator/iterator_traits.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_pointer.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/nullptr.hpp>
#include <pstade/oven/distance.hpp>
#include "./is_lightweight_proxy.hpp"
#include "./range_adaptor.hpp"


namespace pstade { namespace oven {


namespace pointer_range_detail {


    template< class ContiguousRange >
    struct range_pointer
    {
        typedef typename boost::range_result_iterator<ContiguousRange>::type iter_t;
        typedef typename boost::iterator_pointer<iter_t>::type type;
    };


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


} // namespace pointer_range_detail


template< class ContiguousRange >
struct pointer_range :
    pointer_range_detail::super_<ContiguousRange>::type
{
    typedef typename pointer_range_detail::super_<ContiguousRange>::type super_t;

    explicit pointer_range(ContiguousRange& vec) :
        super_t(pointer_range_detail::make_super(vec))
    { }
};


namespace pointer_range_detail {


    struct baby_generator
    {
        template< class ContiguousRange >
        struct result
        {
            typedef const pointer_range<ContiguousRange> type;
        };

        template< class Result, class ContiguousRange >
        Result call(ContiguousRange& rng)
        {
            return Result(rng);
        }
    };


} // namespace pointer_range_detail



PSTADE_EGG_FUNCTION(make_pointer_range, pointer_range_detail::baby_generator)
PSTADE_OVEN_RANGE_ADAPTOR(pointers, pointer_range_detail::baby_generator)


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::pointer_range, 1)


#endif
