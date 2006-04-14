#ifndef PSTADE_TOMATO_MESSAGE_LOOP_RUN_MESSAGE_LOOP_HPP
#define PSTADE_TOMATO_MESSAGE_LOOP_RUN_MESSAGE_LOOP_HPP


// PStade.Tomato
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/sdk/windows.hpp>
#include <boost/microsoft/wtl/app.hpp> // CMessageLoop
#include "../boolean_cast.hpp"
#include "./on_idle.hpp"
#include "./pre_translate_message.hpp"


namespace pstade { namespace tomato {


namespace run_message_loop_detail {


	inline
	bool is_idle_message(MSG& msg)
	{
		return tomato::boolean(WTL::CMessageLoop::IsIdleMessage(&msg));
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


#endif
