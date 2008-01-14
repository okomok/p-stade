#ifndef PSTADE_GRAVY_DECIPOINT_FONT_FROM_HEIGHT_HPP
#define PSTADE_GRAVY_DECIPOINT_FONT_FROM_HEIGHT_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of:
//
// WTL::CLogFont::GetDeciPointHeight and WTL::CFont::CreatePointFontIndirect


#include <pstade/pod_constant.hpp>
#include "./dc_ref.hpp"
#include "./screen_dc_if_null.hpp"
#include "./sdk/windows.hpp"


namespace pstade { namespace gravy {


    namespace decipoint_font_height_detail {


        inline
        LONG aux(LONG lfHeight, dc_ref dc)
        {
#if !defined(_WIN32_WCE)
            POINT ptOrg = { 0, 0 };
            ::DPtoLP(dc, &ptOrg, 1);
            POINT pt = { 0, 0 };
            pt.y = abs(lfHeight) + ptOrg.y;
            ::LPtoDP(dc, &pt, 1);
            return ::MulDiv(pt.y, 720, ::GetDeviceCaps(dc, LOGPIXELSY));
#else
            return ::MulDiv(abs(lfHeight), 720, ::GetDeviceCaps(dc, LOGPIXELSY));
#endif
        }


    } // namespace decipoint_font_height



    struct T_decipoint_font_height
    {
        typedef LONG result_type;

        LONG operator()(LONG lfHeight, HDC hDC) const
        {
            screen_dc_if_null dc(hDC);
            return decipoint_font_height_detail::aux(lfHeight, dc.handle());
        }
    };


    PSTADE_POD_CONSTANT((T_decipoint_font_height), decipoint_font_height) = {};


} } // namespace pstade::gravy


#endif
