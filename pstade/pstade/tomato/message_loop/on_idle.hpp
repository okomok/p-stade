#pragma once

#include <pstade/overload.hpp>
#include <pstade/null_ptr.hpp>
#include "../cast/boolean_cast.hpp"
#include "../diagnostic/verify.hpp"

namespace pstade { namespace tomato {


///////////////////////////////////////////////////////////////////////////////
// on_idle
//
template< class MessageLoop > inline
bool on_idle(MessageLoop& loop, int count)
{
	return pstade_tomato_on_idle(loop, count, overload());
}


} } // namespace pstade::tomato


///////////////////////////////////////////////////////////////////////////////
// default
//
template< class MessageLoop > inline
bool pstade_tomato_on_idle(MessageLoop& loop, int count, ...)
{
	return loop.pstade_tomato_on_idle(count);
}


///////////////////////////////////////////////////////////////////////////////
// WTL::CMessageLoop
//
inline bool pstade_tomato_on_idle(WTL::CMessageLoop& loop, int, pstade::overload)
{
	// See: http://groups.yahoo.com/group/wtl/message/13144
	BOOL bContinue = FALSE;
	for (int i = 0, size = loop.m_aIdleHandler.GetSize(); i < size; ++i) {
		WTL::CIdleHandler *pIdleHandler = loop.m_aIdleHandler[i];
		pstade::tomato::verify(pIdleHandler != pstade::null_ptr);
		bContinue |= pIdleHandler->OnIdle();
	}

	return pstade::tomato::boolean_cast<bool>(bContinue);
}

