#ifndef PSTADE_OVEN_COPY_HPP
#define PSTADE_OVEN_COPY_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Use copy(rng|filtered(), out) instead of copy_if. 


#include <algorithm> // copy
#include <boost/assert.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/result_iterator.hpp>
#include <boost/type_traits/add_pointer.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/remove_extent.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/oven/distance.hpp>


namespace pstade { namespace oven {


namespace copy_detail {


    template< class Array >
    struct array_to_pointer_decay :
        boost::add_pointer<
            typename boost::remove_extent<Array>::type
        >
    { };


    struct baby
    {
        template< class Range, class OutIterOrArray >
        struct result : // Egg asks for Result by using reference.
            boost::mpl::eval_if< boost::is_array<OutIterOrArray>,
                array_to_pointer_decay<OutIterOrArray>,
                boost::mpl::identity<OutIterOrArray>
            >
        { };

        template< class Result, class Range, class OutIter >
        Result call(const Range& rng, OutIter out)
        {
            return std::copy(boost::begin(rng), boost::end(rng), out);
        }
    };


    struct range_baby
    {
        template< class RangeIn, class RangeOut >
        struct result :
            boost::range_result_iterator<RangeOut>
        { };

        template< class Result, class RangeIn, class RangeOut >
        Result call(const RangeIn& in, RangeOut& out)
        {
            BOOST_ASSERT(oven::distance(in) <= oven::distance(out) && "out of range");
            return std::copy(boost::begin(in), boost::end(in), boost::begin(out));
        }
    };


} // namespace copy_detail


PSTADE_EGG_FUNCTION(copy, copy_detail::baby)
PSTADE_EGG_FUNCTION(copies, copy_detail::range_baby)


} } // namespace pstade::oven


#endif
