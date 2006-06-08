#ifndef PSTADE_PIZZA_GET_WRITE_REBAR_HPP
#define PSTADE_PIZZA_GET_WRITE_REBAR_HPP


// PStade.Pizza
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if !defined(_WIN32_WCE)


#include <algorithm> // stable_sort
#include <vector>
#include <boost/assert.hpp>
#include <boost/foreach.hpp>
#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/apple/wtl/ctrls.hpp> // CReBarCtrl
#include <pstade/candy/add.hpp>
#include <pstade/candy/mask.hpp>
#include <pstade/candy/remove.hpp>
#include <pstade/require.hpp>
#include <pstade/tomato/diet/valid.hpp>
#include <pstade/tomato/rebar/add_rebar_band.hpp>
#include <pstade/tomato/rebar/modify_rebar_band_style.hpp>
#include <pstade/tomato/rebar/show_rebar_band.hpp>
#include <pstade/tomato/rebar/rebar_band_runtime_styles.hpp>
#include <pstade/tomato/size_initialize.hpp>
#include <pstade/tomato/tstring.hpp>
#include "../error.hpp"
#include "../integer.hpp"
#include "../set_integer.hpp"


namespace pstade { namespace pizza {


template< class Profile >
void write_rebar(Profile& pr, HWND hWndReBar)
{
    BOOST_ASSERT(diet::valid(hWndReBar));

    WTL::CReBarCtrl rebar(hWndReBar);

    for (UINT uIndex = 0, uCount = rebar.GetBandCount(); uIndex < uCount; ++uIndex) {
        REBARBANDINFO info; {
            info|tomato::size_initialized;
            info.fMask = RBBIM_SIZE | RBBIM_STYLE | RBBIM_CHILD;
            PSTADE_REQUIRE(rebar.GetBandInfo(uIndex, &info));
        }

        tomato::tstring buf; {
            tomato::tstringstream os;
            int id = ::GetDlgCtrlID(info.hwndChild);
            PSTADE_REQUIRE(id != 0);
            os << _T("rebar.band#") << id;
            buf = os.str();
        }

        candy::mask(info.fStyle, tomato::rebar_band_runtime_styles::value);

        pizza::set_integer(pr, buf + _T(".index"),  uIndex);
        pizza::set_integer(pr, buf + _T(".fStyle"), info.fStyle);
        pizza::set_integer(pr, buf + _T(".cx"),     info.cx);
    }
}


struct rebar_band_info
{
    HWND hwndChild;         // cannot be NULL
    UINT fStyle;            // can be 0
    const TCHAR *lpText;    // cannot be 0
};


namespace rebar_detail {


    template< class ReBarBandInfoRange >
    bool is_valid(ReBarBandInfoRange& infos)
    {
        BOOST_FOREACH (const rebar_band_info& info, infos) {
            if (!diet::valid(info.hwndChild))
                return false;
            if (!diet::valid(info.lpText))
                return false;
        }

        return true;
    }


    struct band_info_impl : rebar_band_info
    {
        int m_index;
        UINT m_cx;
        band_info_impl(const rebar_band_info& info, int index, UINT cx) :
            rebar_band_info(info), m_index(index), m_cx(cx)
        { }
    };


    inline bool band_info_impl_lt(const band_info_impl& info1, const band_info_impl& info2)
    {
        return info1.m_index < info2.m_index;
    }


} // namespace rebar_detail


template< class Profile, class ReBarBandInfoRange >
void get_rebar(Profile& pr, HWND hWndReBar, const ReBarBandInfoRange& infos)
{
    BOOST_ASSERT(diet::valid(hWndReBar));
    BOOST_ASSERT(rebar_detail::is_valid(infos));

    std::vector<rebar_detail::band_info_impl> info_impls;

    BOOST_FOREACH (rebar_band_info info, infos) { // copy info

        tomato::tstring buf; {
            int id = ::GetDlgCtrlID(info.hwndChild);
            PSTADE_REQUIRE(id != 0);
            tomato::tstringstream os;
            os << _T("rebar.band#") << id;
            buf = os.str();
        }

        int index = 256; // if value not found, push it back.
        UINT cx = 0;
        try {
            index = pizza::integer(pr, buf + _T(".index"));
            UINT fStyle = pizza::integer(pr, buf + _T(".fStyle"));
            cx = pizza::integer(pr, buf + _T(".cx"));

            // overwrite user default specifications
            candy::remove(info.fStyle, tomato::rebar_band_runtime_styles::value);
            candy::add(info.fStyle, fStyle);
        }
        catch (error&) {
            // not found
        }

        rebar_detail::band_info_impl tmp_for_atl3(info, index, cx);
        info_impls.push_back(tmp_for_atl3);

    } // BOOST_FOREACH

    std::stable_sort(
        boost::begin(info_impls), boost::end(info_impls),
        &rebar_detail::band_info_impl_lt
    );

    BOOST_FOREACH (const rebar_detail::band_info_impl& info, info_impls) {
        tomato::add_rebar_band(hWndReBar, info.hwndChild, info.fStyle, info.lpText, info.m_cx);
    }

    // Workaround WINBUG?:
    //   Hidden band can be seen through the gap in the gripper
    //   and I guess Win32 doesn't support RBBS_GRIPPERALWAYS correctly.
    BOOST_FOREACH (const rebar_detail::band_info_impl& info, info_impls) {
        tomato::show_rebar_band(hWndReBar,
            ::GetDlgCtrlID(info.hwndChild), !candy::test(info.fStyle, RBBS_HIDDEN)
        );
    }
}


} } // namespace pstade::pizza


#endif // !defined(_WIN32_WCE)


#endif
