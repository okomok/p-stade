#pragma once

#include "./on_idle.hpp"
#include "./pre_translate_message.hpp"
#include "./wtl_cmessage_loop_functions.hpp"

namespace pstade { namespace tomato {


struct message_loop
{
	message_loop()
	{
		tomato::add_message_loop(&m_impl);
	}

	~message_loop()
	{
		tomato::remove_message_loop();
	}

	bool pstade_tomato_pre_translate_message(MSG& msg)
	{
		return tomato::pre_translate_message(m_impl, msg);
	}

	bool pstade_tomato_on_idle(int count)
	{
		return tomato::on_idle(m_impl, count);
	}

private:
	WTL::CMessageLoop m_impl;
};


} } // namespace pstade::tomato
