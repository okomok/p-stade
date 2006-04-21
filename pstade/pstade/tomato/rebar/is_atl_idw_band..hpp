#ifndef PSTADE_TOMATO_REBAR_IS_ATL_IDW_BAND_HPP
#define PSTADE_TOMATO_REBAR_IS_ATL_IDW_BAND_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <boost/microsoft/wtl/res.hpp> // ATL_IDW_BAND_FIRST/LAST


namespace pstade { namespace tomato {


inline
bool is_atl_idw_band(UINT uID)
{
    return ATL_IDW_BAND_FIRST <= uID && uID <= ATL_IDW_BAND_LAST;
}


} } // namespace pstade::tomato


#endif
