#ifndef PSTADE_GRAVY_FONT_HEIGHT_FROM_DECIPOINT_HPP
#define PSTADE_GRAVY_FONT_HEIGHT_FROM_DECIPOINT_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of:
//
// WTL::CLogFont::SetHeightFromDeciPoint


#include <pstade/pod_constant.hpp>
#include "./dc_ref.hpp"
#include "./screen_dc_if_null.hpp"
#include "./sdk/windows.hpp"


namespace pstade { namespace gravy {


    namespace font_height_from_decipoint_detail {


        inline
        LONG aux(LONG lDeciPtHeight, dc_ref dc)
        {
#if !defined(_WIN32_WCE)
            POINT pt = { 0, 0 };
            pt.y = ::MulDiv(::GetDeviceCaps(dc, LOGPIXELSY), lDeciPtHeight, 720);
            ::DPtoLP(dc, &pt, 1);
            POINT ptOrg = { 0, 0 };
            ::DPtoLP(dc, &ptOrg, 1);
            return -abs(pt.y - ptOrg.y);
#else
            return -abs(::MulDiv(::GetDeviceCaps(dc, LOGPIXELSY), lDeciPtHeight, 720));
#endif // !defined(_WIN32_WCE)
        }


    } // namespace font_height_from_decipoint_detail


    struct op_font_height_from_decipoint
    {
        typedef LONG result_type;

        LONG operator()(LONG lDeciPtHeight, HDC hDC) const
        {
            screen_dc_if_null dc(hDC);
            return font_height_from_decipoint_detail::aux(lDeciPtHeight, dc.handle());
        }
    };


    PSTADE_POD_CONSTANT((op_font_height_from_decipoint), font_height_from_decipoint) = {};


} } // namespace pstade::gravy


#endif
