#ifndef PSTADE_PIZZA_GET_WRITE_LOGFONT_HPP
#define PSTADE_PIZZA_GET_WRITE_LOGFONT_HPP


// PStade.Pizza
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/oven/array_protect_range.hpp>
#include <pstade/oven/copy.hpp>
#include <pstade/require.hpp>
#include <pstade/tomato/gdi/decipoint_font_height.hpp>
#include <pstade/tomato/gdi/font_height_from_decipoint.hpp>
#include "../integer.hpp"
#include "../set_integer.hpp"
#include "../set_string.hpp"
#include "../string.hpp"


namespace pstade { namespace pizza {


template< class Profile >
void write_logfont(Profile& pr, const LOGFONT& lf, HDC hDC = NULL)
{
    pizza::set_string (pr, _T("logfont.lfFaceName"),    lf.lfFaceName);
    pizza::set_integer(pr, _T("logfont.decipointHeight"), tomato::decipoint_font_height(lf.lfHeight, hDC));
    pizza::set_integer(pr, _T("logfont.lfWeight"),      lf.lfWeight);
    pizza::set_integer(pr, _T("logfont.lfItalic"),      lf.lfItalic);
    pizza::set_integer(pr, _T("logfont.lfWeight"),      lf.lfWeight);
    pizza::set_integer(pr, _T("logfont.lfUnderline"),   lf.lfUnderline);
    pizza::set_integer(pr, _T("logfont.lfStrikeOut"),   lf.lfStrikeOut);
    pizza::set_integer(pr, _T("logfont.lfCharSet"),     lf.lfCharSet);
}


template< class Profile >
LOGFONT get_logfont(Profile& pr, HDC hDC = NULL)
{
    LOGFONT lf = { 0 };

    oven::copies(pizza::string(pr, _T("logfont.lfFaceName")), lf.lfFaceName|oven::array_protected);
    PSTADE_REQUIRE(oven::is_null_terminated(lf.lfFaceName|oven::array_protected));
    DWORD dwHeight =    pizza::integer(pr, _T("logfont.decipointHeight"));
    lf.lfHeight =       tomato::font_height_from_decipoint(dwHeight, hDC);
    lf.lfWeight =       pizza::integer(pr, _T("logfont.lfWeight"));
    lf.lfItalic =       pizza::integer(pr, _T("logfont.lfItalic"));
    lf.lfUnderline =    pizza::integer(pr, _T("logfont.lfUnderLine"));
    lf.lfStrikeOut =    pizza::integer(pr, _T("logfont.lfStrikeOut"));
    lf.lfCharSet =      pizza::integer(pr, _T("logfont.lfCharSet"));

    return lf;
}


} } // namespace pstade::pizza


#endif
