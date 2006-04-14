#ifndef PSTADE_TOMATO_WINDOW_REGISTER_WINDOW_MESSAGE_HPP
#define PSTADE_TOMATO_WINDOW_REGISTER_WINDOW_MESSAGE_HPP


// PStade.Tomato
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/microsoft/sdk/tchar.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <pstade/instance.hpp>
#include "../tstringize.hpp"


#define PSTADE_TOMATO_REGISTER_WINDOW_MESSAGE(Name, Msg) \
	PSTADE_INSTANCE_ARGS( \
		const UINT, \
		Name, \
		(pstade::tomato::register_window_message_detail::check( \
			::RegisterWindowMessage(PSTADE_TOMATO_TSTRINGIZE(Msg)) \
		)) \
	) \
/**/


namespace pstade { namespace tomato { namespace register_window_message_detail {


inline
UINT check(UINT uMsg)
{
	BOOST_ASSERT(uMsg != 0);
	return uMsg;
}


} } } // namespace pstade::tomato::register_window_message_detail


#endif
