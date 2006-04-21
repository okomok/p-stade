#ifndef PSTADE_INTEGRAL_CAST_HPP
#define PSTADE_INTEGRAL_CAST_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/identity.hpp>
#include <boost/numeric/conversion/cast.hpp> // numeric_cast
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_integral.hpp>


namespace pstade {


template< class TargetT, class SourceT > inline const
TargetT integral_cast(SourceT arg)
{
    BOOST_STATIC_ASSERT((boost::is_integral<TargetT>::value));
    BOOST_STATIC_ASSERT((boost::is_integral<SourceT>::value));

    return boost::numeric_cast<TargetT>(arg); // :-)
}


namespace integral_cast_detail {


    template< class SourceT >
    struct temp
    {
        explicit temp(SourceT src) :
            m_src(src)
        { }

        template< class TargetT >
        operator TargetT() const
        {
            return pstade::integral_cast<TargetT>(m_src);
        }

    private:
        SourceT m_src;
    };


} // namespace integral_cast_detail


template< class SourceT > inline const
integral_cast_detail::temp<SourceT> integral(SourceT src)
{
    return integral_cast_detail::temp<SourceT>(src);
}


} // namespace pstade


#endif
