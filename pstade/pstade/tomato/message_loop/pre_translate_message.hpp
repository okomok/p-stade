#pragma once

#include <pstade/overload.hpp>
#include <pstade/null_ptr.hpp>

namespace pstade { namespace tomato {


///////////////////////////////////////////////////////////////////////////////
// pre_translate_message
//
template< class MessageLoop > inline
bool pre_translate_message(MessageLoop& loop, MSG& msg)
{
	return pstade_tomato_pre_translate_message(loop, msg, overload());
}


} } // namespace pstade::tomato


///////////////////////////////////////////////////////////////////////////////
// default
//
template< class MessageLoop > inline
bool pstade_tomato_pre_translate_message(MessageLoop& loop, MSG& msg, ...)
{
	return loop.pstade_tomato_pre_translate_message(msg);
}


///////////////////////////////////////////////////////////////////////////////
// WTL::CMessageLoop
//
inline bool pstade_tomato_pre_translate_message(WTL::CMessageLoop& loop, MSG& msg, pstade::overload)
{
	// loop backwards
	for (int i = loop.m_aMsgFilter.GetSize() - 1; i >= 0; --i) {
		WTL::CMessageFilter *pMessageFilter = loop.m_aMsgFilter[i];
		ATLASSERT(pMessageFilter != pstade::null_ptr);
		if (pMessageFilter->PreTranslateMessage(&msg))
			return true;
	}
	return false; // not translated
}

