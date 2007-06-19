#ifndef PSTADE_TOMATO_GRAVY_C_STR_HPP
#define PSTADE_TOMATO_GRAVY_C_STR_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/gravy/c_str.hpp>
#include <pstade/gravy/sdk/tchar.hpp>
#include "./atl/config.hpp" // ATL_VER, CSIMPLESTRINGT_TEMPLATE_PARAMS/ARGS
#include "./atl/simpstr_fwd.hpp" // CSimpleStringT
#include "./wtl/misc.hpp" // CString


namespace pstade_gravy_extension {


    inline
    TCHAR const *pstade_gravy_(c_str, WTL::CString const& str)
    {
        return str;
    }


    // 'enable_if<is_ATL_CSimpleStringT,...>' is useless here, which ignores class hierarchy.
    template< PSTADE_TOMATO_ATL_CSIMPLESTRINGT_TEMPLATE_PARAMS > inline
    BaseType const *pstade_gravy_(c_str, ATL::CSimpleStringT< PSTADE_TOMATO_ATL_CSIMPLESTRINGT_TEMPLATE_ARGS > const& str)
    {
        return str;
    }


} // namespace pstade_gravy_extension


#endif
