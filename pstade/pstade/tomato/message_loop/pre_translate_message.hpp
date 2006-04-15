#ifndef PSTADE_TOMATO_MESSAGE_LOOP_PRE_TRANSLATE_MESSAGE_HPP
#define PSTADE_TOMATO_MESSAGE_LOOP_PRE_TRANSLATE_MESSAGE_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/microsoft/wtl/app.hpp> // CMessageLoop, CMessageFilter
#include <pstade/overload.hpp>
#include <pstade/nullptr.hpp>


namespace pstade { namespace tomato {


template< class MessageLoop > inline
bool pre_translate_message(MessageLoop& loop, MSG& msg)
{
	return pstade_tomato_pre_translate_message(loop, msg, overload());
}


} } // namespace pstade::tomato


// WTL::CMessageLoop
//
inline
bool pstade_tomato_pre_translate_message(WTL::CMessageLoop& loop, MSG& msg, pstade::overload)
{
	// loop backwards
	for (int i = loop.m_aMsgFilter.GetSize() - 1; i >= 0; --i) {
		WTL::CMessageFilter *pMessageFilter = loop.m_aMsgFilter[i];
		BOOST_ASSERT(pMessageFilter != PSTADE_NULLPTR);
		if (pMessageFilter->PreTranslateMessage(&msg))
			return true;
	}

	return false; // not translated
}


#endif
