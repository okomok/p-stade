#ifndef PSTADE_APPLE_ATL_IS_ATL_STRING_HPP
#define PSTADE_APPLE_ATL_IS_ATL_STRING_HPP


// PStade.Apple
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/or.hpp>
#include "./is_ATL_CFixedStringT.hpp"
#include "./is_ATL_CSimpleStringT.hpp"
#include "./is_ATL_CStaticString.hpp"
#include "./is_ATL_CStringT.hpp"


namespace pstade { namespace apple {


template< class T >
struct is_ATL_string :
    boost::mpl::or_<
        is_ATL_CFixedStringT<T>,
        is_ATL_CSimpleStringT<T>,
        is_ATL_CStaticString<T>,
        is_ATL_CStringT<T>
    >
{ };


} } // namespace pstade::apple


#endif
