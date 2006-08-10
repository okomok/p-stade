#ifndef PSTADE_INTEGRAL_CAST_HPP
#define PSTADE_INTEGRAL_CAST_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/assert.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/numeric/conversion/cast.hpp> // numeric_cast
#include <boost/type_traits/is_integral.hpp>
#include <pstade/nonassignable.hpp>


namespace pstade {


template< class TargetT, class SourceT > inline
TargetT integral_cast(SourceT src)
{
    BOOST_MPL_ASSERT((boost::is_integral<TargetT>));
    BOOST_MPL_ASSERT((boost::is_integral<SourceT>));

    return boost::numeric_cast<TargetT>(src); // :-)
}


namespace integral_cast_detail {


    template< class SourceT >
    struct temp :
        private nonassignable
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


template< class SourceT > inline
integral_cast_detail::temp<SourceT> const
integral(SourceT src)
{
    return integral_cast_detail::temp<SourceT>(src);
}


} // namespace pstade


#endif
