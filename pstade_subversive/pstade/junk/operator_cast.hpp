#ifndef PSTADE_OPERATOR_CAST_HPP
#define PSTADE_OPERATOR_CAST_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/const_overloaded.hp>


namespace pstade {


template< class TargetT, class SourceT > inline const
typename const_overloaded<TargetT, SourceT>::type
operator_cast(SourceT& src)
{
    return src.operator TargetT();
}


template< class TargetT, class SourceT > inline const
TargetT
operator_cast(const SourceT& src)
{
    return src.operator TargetT();
}


} // namespace pstade


#endif
