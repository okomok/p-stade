#ifndef PSTADE_TOMATO_MESSAGE_LOOP_WTL_CMESSAGE_LOOP_FUNCTIONS_HPP
#define PSTADE_TOMATO_MESSAGE_LOOP_WTL_CMESSAGE_LOOP_FUNCTIONS_HPP


// PStade.Tomato
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/microsoft/atl/module.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <boost/microsoft/wtl/app.hpp> // CMessageLoop
#include <pstade/nullptr.hpp>
#include <pstade/require.hpp>


namespace pstade { namespace tomato {


inline
void add_message_loop(WTL::CMessageLoop *pMsgLoop)
{
	BOOST_ASSERT(pMsgLoop != PSTADE_NULLPTR);

	PSTADE_REQUIRE(_Module.AddMessageLoop(pMsgLoop));
}


inline
void remove_message_loop()
{
	PSTADE_REQUIRE(_Module.RemoveMessageLoop());
}


inline
void add_message_filter(WTL::CMessageFilter *pMessageFilter, DWORD dwThreadID = ::GetCurrentThreadId())
{
	BOOST_ASSERT(pMessageFilter != PSTADE_NULLPTR);

	WTL::CMessageLoop *pLoop = _Module.GetMessageLoop(dwThreadID);
	BOOST_ASSERT(pLoop != PSTADE_NULLPTR);

	PSTADE_REQUIRE(pLoop->AddMessageFilter(pMessageFilter));
}


inline
void remove_message_filter(WTL::CMessageFilter *pMessageFilter, DWORD dwThreadID = ::GetCurrentThreadId())
{
	BOOST_ASSERT(pMessageFilter != PSTADE_NULLPTR);

	WTL::CMessageLoop *pLoop = _Module.GetMessageLoop(dwThreadID);
	BOOST_ASSERT(pLoop != PSTADE_NULLPTR);

	PSTADE_REQUIRE(pLoop->RemoveMessageFilter(pMessageFilter));
}


inline
void add_idle_handler(WTL::CIdleHandler *pIdleHandler, DWORD dwThreadID = ::GetCurrentThreadId())
{
	BOOST_ASSERT(pIdleHandler != PSTADE_NULLPTR);

	WTL::CMessageLoop *pLoop = _Module.GetMessageLoop(dwThreadID);
	BOOST_ASSERT(pLoop != PSTADE_NULLPTR);

	PSTADE_REQUIRE(pLoop->AddIdleHandler(pIdleHandler));
}


inline
void remove_idle_handler(WTL::CIdleHandler *pIdleHandler, DWORD dwThreadID = ::GetCurrentThreadId())
{
	BOOST_ASSERT(pIdleHandler != PSTADE_NULLPTR);

	WTL::CMessageLoop *pLoop = _Module.GetMessageLoop(dwThreadID);
	BOOST_ASSERT(pLoop != PSTADE_NULLPTR);

	PSTADE_REQUIRE(pLoop->RemoveIdleHandler(pIdleHandler));
}


} } // namespace pstade::tomato


#endif
