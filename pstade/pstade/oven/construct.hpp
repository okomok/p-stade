#ifndef PSTADE_OVEN_CONSTRUCT_HPP
#define PSTADE_OVEN_CONSTRUCT_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/utility/addressof.hpp>
#include <boost/utility/enable_if.hpp>
#include <pstade/apple/has_range_constructor.hpp>
#include <pstade/overload.hpp>


namespace pstade { namespace oven {


// constructor
//

namespace construct_detail {


    template< class T, class Range > inline
    typename boost::enable_if< apple::has_range_constructor<T>,
    T>::type pstade_oven_construct(Range& rng, overload<T>)
    {
        return T(boost::begin(rng), boost::end(rng));
    }


} // namespace construct_detail


template< class T, class Range > inline
T constructor(const Range& rng)
{
    // Under: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2005/n1893.pdf
    // using namespace(T);

    using namespace construct_detail;
    return pstade_oven_construct(rng, overload<T>());
}


// construct
//

namespace construct_detail {


    template< class Range >
    struct temp
    {
        explicit temp(const Range& rng) :
            m_prng(boost::addressof(rng))
        { }

        template< class T >
        operator T() const
        {
            return oven::constructor<T>(*m_prng);
        }

    private:
        const Range *m_prng;
    };


} // namespace construct_detail


template< class Range > inline const
construct_detail::temp<Range> construct(const Range& rng)
{
    // Topic:
    // When tmp is missing under GCC3.4.4,
    // it sometimes runs a foul of strange behaviors
    // if conversion template target is reference type.

    construct_detail::temp<Range> tmp(rng);
    return tmp;
}


} } // namespace pstade::oven


#endif
