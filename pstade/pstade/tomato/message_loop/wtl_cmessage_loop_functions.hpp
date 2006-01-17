#pragma once

#include <pstade/null_ptr.hpp>
#include "../diagnostic/verify.hpp"

namespace pstade { namespace tomato {


inline void add_message_loop(WTL::CMessageLoop *pMsgLoop)
{
	ATLASSERT(pMsgLoop != pstade::null_ptr);

	tomato::verify(_Module.AddMessageLoop(pMsgLoop));
}


inline void remove_message_loop()
{
	tomato::verify(_Module.RemoveMessageLoop());
}


inline void add_message_filter(WTL::CMessageFilter *pMessageFilter, DWORD dwThreadID = ::GetCurrentThreadId())
{
	ATLASSERT(pMessageFilter != pstade::null_ptr);

	WTL::CMessageLoop *pLoop = _Module.GetMessageLoop(dwThreadID);
	ATLASSERT(pLoop != pstade::null_ptr);

	tomato::verify(pLoop->AddMessageFilter(pMessageFilter));
}


inline void remove_message_filter(WTL::CMessageFilter *pMessageFilter, DWORD dwThreadID = ::GetCurrentThreadId())
{
	ATLASSERT(pMessageFilter != pstade::null_ptr);

	WTL::CMessageLoop *pLoop = _Module.GetMessageLoop(dwThreadID);
	ATLASSERT(pLoop != pstade::null_ptr);

	tomato::verify(pLoop->RemoveMessageFilter(pMessageFilter));
}


inline void add_idle_handler(WTL::CIdleHandler *pIdleHandler, DWORD dwThreadID = ::GetCurrentThreadId())
{
	ATLASSERT(pIdleHandler != pstade::null_ptr);

	WTL::CMessageLoop *pLoop = _Module.GetMessageLoop(dwThreadID);
	ATLASSERT(pLoop != pstade::null_ptr);

	tomato::verify(pLoop->AddIdleHandler(pIdleHandler));
}


inline void remove_idle_handler(WTL::CIdleHandler *pIdleHandler, DWORD dwThreadID = ::GetCurrentThreadId())
{
	ATLASSERT(pIdleHandler != pstade::null_ptr);

	WTL::CMessageLoop *pLoop = _Module.GetMessageLoop(dwThreadID);
	ATLASSERT(pLoop != pstade::null_ptr);

	tomato::verify(pLoop->RemoveIdleHandler(pIdleHandler));
}


} } // namespace pstade::tomato
