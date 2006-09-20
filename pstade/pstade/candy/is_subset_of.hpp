#ifndef PSTADE_CANDY_IS_SUBSET_OF_HPP
#define PSTADE_CANDY_IS_SUBSET_OF_HPP


// PStade.Candy
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace candy {


template< class Flags0, class Flags1 > inline
bool is_subset_of(Flags0 const& fs0, Flags1 const& fs1)
{
    return (fs0 & fs1) == fs0;
}


} } // namespace pstade::candy


#endif
