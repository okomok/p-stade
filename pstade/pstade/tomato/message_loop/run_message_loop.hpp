#pragma once

#include "../cast/boolean_cast.hpp"
#include "./on_idle.hpp"
#include "./pre_translate_message.hpp"

namespace pstade { namespace tomato {


namespace run_message_loop_detail {

	inline bool is_idle_message(MSG& msg)
	{
		return tomato::boolean_cast<bool>(WTL::CMessageLoop::IsIdleMessage(&msg));
	}

} // namespace run_message_loop_detail


template< class MessageLoop >
int run_message_loop(MessageLoop& loop)
{
	MSG msg;
	bool idle = true;
	int idle_count = 0;
	BOOL bRet;

	for (;;) {
		while (idle && !::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {
			if (!tomato::on_idle(loop, idle_count++))
				idle = false;
		}

		bRet = ::GetMessage(&msg, NULL, 0, 0);

		if (bRet == -1) {
			ATLTRACE2(WTL::atlTraceUI, 0, _T("::GetMessage returned -1 (error)\n"));
			continue;		// error, don't process
		}
		else if (bRet == FALSE) {
			ATLTRACE2(WTL::atlTraceUI, 0, _T("pstade::tomato::run_message_loop - exiting\n"));
			break;			// WM_QUIT, exit message loop
		}

		if (!tomato::pre_translate_message(loop, msg)) {
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		if (run_message_loop_detail::is_idle_message(msg)) {
			idle = true;
			idle_count = 0;
		}
	} // for (;;)

	return msg.wParam;
}


} } // namespace pstade::tomato
