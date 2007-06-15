#ifndef PSTADE_TOMATO_REBAR_BAND_RUNTIME_STYLES_HPP
#define PSTADE_TOMATO_REBAR_BAND_RUNTIME_STYLES_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/gravy/sdk/windows.hpp>
#include <pstade/static_c.hpp>


namespace pstade { namespace tomato {


    struct rebar_band_runtime_styles :
        static_c<UINT, RBBS_BREAK | RBBS_HIDDEN | RBBS_NOGRIPPER>
    { };


} } // namespace pstade::tomato


#endif
