#ifndef PSTADE_CANDY_IS_SUBSET_OF_HPP
#define PSTADE_CANDY_IS_SUBSET_OF_HPP


// PStade.Candy
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./union.hpp"


namespace pstade { namespace candy {


template< class Flags0, class Flags1 > inline
bool is_subset_of(Flags0 fs0, Flags1 fs1)
{
    return candy::union_(fs0, fs1) == fs1;
}


} } // namespace pstade::candy


#endif
