#pragma once

/// \file tstoi.hpp
/// tomato::tstoi works around CRT.

namespace pstade { namespace tomato {


/// \cond OUTPUT_DETAIL
namespace tstoi_detail {

	inline bool is_space(TCHAR ch)
	{
		return ch == _T(' ');
	}

	inline bool is_digit(TCHAR ch)
	{
		return ch >= _T('0') && ch <= _T('9');
	}

	inline bool is_sign(TCHAR ch)
	{
		return ch == _T('-') || ch == _T('+');
	}

	inline bool is_minus(TCHAR ch)
	{
		return ch == _T('-');
	}

	inline int to_digit(TCHAR ch)
	{
		ATLASSERT(is_digit(ch));

		return ch - _T('0');
	}

} // namespace tstoi_detail
/// \endcond


inline int tstoi(LPCTSTR psz)
{
	// See: crt/_tstol

	while (tstoi_detail::is_space(*psz)) {
		++psz;
	}

	TCHAR ch = *psz++;
	bool neg = false;

	if (tstoi_detail::is_sign(ch)) {
		if (tstoi_detail::is_minus(ch))
			neg = true;

		ch = *psz++;
	}

	int total = 0;
	while (tstoi_detail::is_digit(ch)) {
		total = 10 * total + tstoi_detail::to_digit(ch);
		ch = *psz++;
	}

	if (neg)
		return -total;
	else
		return total;
}


} } // namespace pstade::tomato
