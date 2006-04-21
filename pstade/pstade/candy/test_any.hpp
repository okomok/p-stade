#ifndef PSTADE_CANDY_TEST_ANY_HPP
#define PSTADE_CANDY_TEST_ANY_HPP


// PStade.Candy
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./empty.hpp"
#include "./intersection.hpp"


namespace pstade { namespace candy {


template< class Flags0, class Flags1 > inline
bool test_any(Flags0 fs0, Flags1 fs1)
{
    return !candy::empty(candy::intersection(fs0, fs1));
}


} } // namespace pstade::candy


#endif
