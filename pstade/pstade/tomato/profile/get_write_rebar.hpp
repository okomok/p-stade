#pragma once

#if !defined(_WIN32_WCE)

#include <atlctrls.h>
#include <boost/foreach.hpp>
#include <pstade/candy/add.hpp>
#include <pstade/candy/mask.hpp>
#include <pstade/candy/remove.hpp>
#include <pstade/stove/push_back.hpp>
#include "../algorithm/stable_sort.hpp"
#include "../cast/boolean_cast.hpp"
#include "../collection/atl_csimplearray.hpp"
#include "../diagnostic/is_valid.hpp"
#include "../diagnostic/verify.hpp"
#include "../rebar/add_rebar_band.hpp"
#include "../rebar/modify_rebar_band_style.hpp"
#include "../rebar/show_rebar_band.hpp"
#include "../rebar/rebar_band_runtime_styles.hpp"
#include "../structure/version_initialize.hpp"
#include "./query_dword.hpp"
#include "./set_dword.hpp"

namespace pstade { namespace tomato {


template< class StringT, class Profile >
void profile_write_rebar(Profile& pr, HWND hWndReBar, const StringT& prefix)
{
	ATLASSERT(tomato::is_valid(hWndReBar));

	WTL::CReBarCtrl rebar(hWndReBar);

	for (UINT uIndex = 0, uCount = rebar.GetBandCount(); uIndex < uCount; ++uIndex) {
		REBARBANDINFO info;
		tomato::version_initialize(info);
		info.fMask = RBBIM_SIZE | RBBIM_STYLE | RBBIM_CHILD;
		tomato::api_verify(rebar.GetBandInfo(uIndex, &info));

		StringT buf = prefix + _T("rebar.band#");
		int id = ::GetDlgCtrlID(info.hwndChild);
		tomato::api_verify(id != 0);
		buf.Append(id);

		candy::mask(info.fStyle, rebar_band_runtime_styles::value);

		tomato::profile_set_dword(pr, buf + _T(".index"), uIndex);
		tomato::profile_set_dword(pr, buf + _T(".fStyle"), info.fStyle);
		tomato::profile_set_dword(pr, buf + _T(".cx"), info.cx);
	}
}


struct rebar_band_info
{
	HWND hwndChild;		// cannot be NULL
	UINT fStyle;			// can be 0
	LPCTSTR lpText;		// can be 0
};


namespace profile_rebar_detail {

	template< class ReBarBandInfoRange >
	bool is_valid_rebar_band_info_range(ReBarBandInfoRange& infos)
	{
		BOOST_FOREACH (const rebar_band_info& info, infos)
		{
			if(!tomato::is_valid(info.hwndChild))
				return false;
		}

		return true;
	}

	struct rebar_band_info_impl : rebar_band_info
	{
		int m_index;
		UINT m_cx;
		rebar_band_info_impl(const rebar_band_info& info, int index, UINT cx) :
			rebar_band_info(info), m_index(index), m_cx(cx)
		{ }
	};

	// functors
	inline bool rebar_band_info_impl_lt(const rebar_band_info_impl& info1, const rebar_band_info_impl& info2)
	{
		return info1.m_index < info2.m_index;
	}

} // namespace profile_rebar_detail


template< class StringT, class Profile, class ReBarBandInfoRange >
void profile_get_rebar(Profile& pr, HWND hWndReBar, const ReBarBandInfoRange& infos, const StringT& prefix)
{
	ATLASSERT(tomato::is_valid(hWndReBar));
	ATLASSERT(profile_rebar_detail::is_valid_rebar_band_info_range(infos));

	ATL::CSimpleArray<profile_rebar_detail::rebar_band_info_impl> info_impls;

	BOOST_FOREACH (rebar_band_info info, infos) { // copy
		int id = ::GetDlgCtrlID(info.hwndChild);
		tomato::api_verify(id != 0);

		StringT buf = prefix + _T("rebar.band#");
		buf.Append(id);

		DWORD dwIndex = 256; // if value not found, push it back.
		DWORD dwStyle = 0, dwCx = 0;
		if (
			tomato::profile_query_dword(pr, buf + _T(".index"), dwIndex) &&
			tomato::profile_query_dword(pr, buf + _T(".fStyle"), dwStyle) &&
			tomato::profile_query_dword(pr, buf + _T(".cx"), dwCx)
		)
		{
			candy::remove(info.fStyle, rebar_band_runtime_styles::value);
			candy::add(info.fStyle, dwStyle);
		}

		// even if value not found, user specifications are used as default.
		stove::push_back(info_impls, profile_rebar_detail::rebar_band_info_impl(info, dwIndex, dwCx));
	} // BOOST_FOREACH

	tomato::stable_sort(info_impls, &profile_rebar_detail::rebar_band_info_impl_lt);

	BOOST_FOREACH (const profile_rebar_detail::rebar_band_info_impl& info, info_impls) {
		tomato::add_rebar_band(hWndReBar, info.hwndChild, info.fStyle, info.lpText, info.m_cx);
	}

	// Workaround WINBUG?:
	//   Hidden band can be seen through the gap in the gripper
	//   and I guess Win32 doesn't support RBBS_GRIPPERALWAYS correctly.
	BOOST_FOREACH (const profile_rebar_detail::rebar_band_info_impl& info, info_impls) {
		tomato::show_rebar_band(
			hWndReBar, ::GetDlgCtrlID(info.hwndChild),
			tomato::boolean_cast<BOOL>(!candy::test(info.fStyle, RBBS_HIDDEN))
		);
	}
}


} } // namespace pstade::tomato

#endif // !defined(_WIN32_WCE)
