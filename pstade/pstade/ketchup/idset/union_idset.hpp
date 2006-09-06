#ifndef PSTADE_KETCHUP_IDSET_UNION_IDSET_HPP
#define PSTADE_KETCHUP_IDSET_UNION_IDSET_HPP


// PStade.Ketchup
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/windows.hpp>


namespace pstade { namespace ketchup {


template< class IDs0, class IDs1 >
struct union_idset
{
    static bool contains(UINT id)
    {
        if (IDs0::contains(id)) { return true; }
        if (IDs1::contains(id)) { return true; }

        return false;
    }
};


} } // namespace pstade::ketchup


#endif
