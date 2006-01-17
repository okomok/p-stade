#pragma once

#include <boost/config.hpp> // for BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE
#include "../diagnostic/is_valid.hpp"
#include "../diagnostic/verify.hpp"
#include "../thread/scoped_lock.hpp"

namespace pstade { namespace tomato {


template< class TagT >
UINT register_window_message(LPCTSTR pszMessage BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(TagT))
{
	ATLASSERT(tomato::is_valid(pszMessage));

	static UINT s_uMessage = 0;

	if (s_uMessage == 0) {
		scoped_lock<WTL::CStaticDataInitCriticalSectionLock> lock;

		if (s_uMessage == 0) {
			s_uMessage = ::RegisterWindowMessage(pszMessage);
			tomato::api_verify(s_uMessage != 0);
		}
	}

	ATLASSERT(s_uMessage != 0);
	return s_uMessage;
}


} } // namespace pstade::tomato
