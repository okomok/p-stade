#ifndef PSTADE_INTEGRAL_CAST_HPP
#define PSTADE_INTEGRAL_CAST_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/assert.hpp>
#include <boost/numeric/conversion/cast.hpp> // numeric_cast
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <pstade/egg/function.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/nonassignable.hpp>


namespace pstade {


template< class To, class From > inline
To integral_cast(From from)
{
    BOOST_MPL_ASSERT((boost::is_integral<To>));
    BOOST_MPL_ASSERT((boost::is_integral<From>));

    return boost::numeric_cast<To>(from);
}


namespace integral_cast_detail {


    template< class From >
    struct temp :
        private nonassignable
    {
        explicit temp(From from) :
            m_from(from)
        { }

        template< class To >
        operator To() const
        {
            return pstade::integral_cast<To>(m_from);
        }

    private:
        From m_from;
    };


    struct baby_auto
    {
        template< class Unused, class From >
        struct result
        {
            typedef typename boost::remove_cv<From>::type from_t;
            typedef temp<from_t> const type;
        };

        template< class Result, class From >
        Result call(From from)
        {
            return Result(from);
        }
    };


} // namespace integral_cast_detail


PSTADE_EGG_FUNCTION(integral, integral_cast_detail::baby_auto)
PSTADE_EGG_PIPABLE(to_integer, integral_cast_detail::baby_auto)


} // namespace pstade


#endif
