#pragma once

// Note:
//   verify, whether debugging or not, throws an exception
//   that means exceptional runtime-error.
//   On the other hand, ATLASSERT checks "static" coding mistakes.
//   I think that it was right for ATL designers not to add ATLVERIFY
//   on the initial version, because it must be meaningless
//   to turn on detection of runtime-error that depend on environment
//   only when debugging.
//   Well, api failure is always runtime-error,
//   so you must use api_verify.

#include <pstade/unused.hpp>

namespace pstade { namespace tomato {


// See: Error definitions of WinError.h 

template< class BooleanT > inline
void verify(BooleanT expr, HRESULT hr = E_FAIL)
{
#if (_ATL_VER >= 0x0700)
	if (!expr)
		ATL::AtlThrow(hr);
#else
	ATLASSERT(expr);
	pstade::unused(expr, hr);
#endif
}


template< class BooleanT > inline
void api_verify(BooleanT expr)
{
#if (_ATL_VER >= 0x0700)
	if (!expr)
		ATL::AtlThrowLastWin32();
#else
	ATLASSERT(expr);
	pstade::unused(expr);
#endif
}


} } // namespace pstade::tomato
