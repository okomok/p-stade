#ifndef PSTADE_CANDY_INTERSECTION_HPP
#define PSTADE_CANDY_INTERSECTION_HPP


// PStade.Candy
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/integral_cast.hpp>
#include "./detail/greater_size.hpp"


namespace pstade { namespace candy {


template< class Flags0, class Flags1 > inline
typename detail::greater_size<Flags0, Flags1>::type
intersection(Flags0 fs0, Flags1 fs1)
{
    // Note:
    //   standard conversion makes smaller type to int, so we must cast to avoid warning.

    return pstade::integral(fs0 & fs1);
}


} } // namespace pstade::candy


#endif
