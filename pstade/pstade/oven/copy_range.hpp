#ifndef PSTADE_OVEN_COPY_RANGE_HPP
#define PSTADE_OVEN_COPY_RANGE_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/utility/enable_if.hpp>
#include <pstade/apple/has_range_constructor.hpp>
#include <pstade/apple/is_boost_range.hpp>
#include <pstade/overload.hpp>
#include "./algorithm.hpp" // copy
#include "./copy_range.hpp"
#include "./distance.hpp"
#include "./range_adaptor.hpp"


namespace pstade { namespace oven {


namespace copy_range_detail {


    template< class T, class Range > inline
    typename boost::enable_if<apple::has_range_constructor<T>,
    T>::type pstade_oven_copy_range(Range& rng, overload<T>)
    {
        return T(boost::begin(rng), boost::end(rng));
    }


} // namespace copy_range_detail


template< class T, class Range > inline
T copy_range(const Range& rng)
{
    // Under: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2005/n1893.pdf
    // using namespace(T);

    using namespace copy_range_detail;
    return pstade_oven_copy_range(rng, overload<T>());
}


namespace copy_range_detail {


    template< class Range >
    struct temp
    {
        explicit temp(const Range& rng) :
            m_prng(boost::addressof(rng))
        { }

        template< class T >
        operator T() const
        {
            return oven::copy_range<T>(*m_prng);
        }

    private:
        const Range *m_prng;
    };


    struct baby
    {
        template< class InRange, class OutRangeOrIter = void>
        struct result
        {
            typedef InRange type;
        };

        template< class InRange >
        struct result<InRange>
        {
            typedef typename boost::remove_cv<InRange>::type rng_t;
            typedef const temp<rng_t> type;
        };

        template< class Result, class InRange, class OutIter >
        typename boost::disable_if< apple::is_boost_range<OutIter>,
        Result>::type call(const InRange& in, OutIter out)
        {
            oven::copy(in, out);
            return in;
        }

        template< class Result, class InRange, class OutRange >
        typename boost::enable_if< apple::is_boost_range<OutRange>,
        Result>::type call(const InRange& in, OutRange& out)
        {
            BOOST_STATIC_ASSERT(!boost::is_const<OutRange>::value);
            BOOST_ASSERT(oven::distance(in) <= oven::distance(out) && "out of range");

            oven::copy(in, boost::begin(out));
            return in;
        }

        template< class Result, class InRange >
        Result call(const InRange& in)
        {
            // Topic:
            // When tmp is missing under GCC3.4.4,
            // it sometimes runs a foul of strange behaviors
            // if conversion template target is reference type.

            Result tmp(in);
            return tmp;
        }
    };


} // namespace copy_range_detail


PSTADE_OVEN_RANGE_ADAPTOR(copied, copy_range_detail::baby)


} } // namespace pstade::oven


#endif
