#ifndef PSTADE_TOMATO_MESSAGE_LOOP_ON_IDLE_HPP
#define PSTADE_TOMATO_MESSAGE_LOOP_ON_IDLE_HPP


// PStade.Tomato
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/microsoft/wtl/app.hpp> // CMessageLoop, CIdleHandler
#include <pstade/overload.hpp>
#include <pstade/nullptr.hpp>
#include "../boolean_cast.hpp"


namespace pstade { namespace tomato {


template< class MessageLoop > inline
bool on_idle(MessageLoop& loop, int count)
{
	return pstade_tomato_on_idle(loop, count, overload());
}


} } // namespace pstade::tomato


// WTL::CMessageLoop
//
inline
bool pstade_tomato_on_idle(WTL::CMessageLoop& loop, int, pstade::overload)
{
	// See: http://groups.yahoo.com/group/wtl/message/13144
	BOOL bContinue = FALSE;
	for (int i = 0, size = loop.m_aIdleHandler.GetSize(); i < size; ++i) {
		WTL::CIdleHandler *pIdleHandler = loop.m_aIdleHandler[i];
		BOOST_ASSERT(pIdleHandler != PSTADE_NULLPTR);
		bContinue |= pIdleHandler->OnIdle();
	}

	return pstade::tomato::boolean(bContinue);
}


#endif
