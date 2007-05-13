#ifndef PSTADE_KETCHUP_IDSET_UNIVERSAL_ID_SET_HPP
#define PSTADE_KETCHUP_IDSET_UNIVERSAL_ID_SET_HPP


// PStade.Ketchup
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/windows.hpp>


namespace pstade { namespace ketchup {


struct universal_idset
{
    static bool contains(UINT)
    {
        return true;
    }
};


} } // namespace pstade::ketchup


#endif
