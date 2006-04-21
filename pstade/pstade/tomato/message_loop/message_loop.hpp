#ifndef PSTADE_TOMATO_MESSAGE_LOOP_MESSAGE_LOOP_HPP
#define PSTADE_TOMATO_MESSAGE_LOOP_MESSAGE_LOOP_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/sdk/windows.hpp>
#include <pstade/overload.hpp>
#include "./on_idle.hpp"
#include "./pre_translate_message.hpp"
#include "./wtl_cmessage_loop_functions.hpp"


namespace pstade { namespace tomato {


struct message_loop
{
    message_loop()
    {
        tomato::add_message_loop(&detail_m_impl);
    }

    ~message_loop()
    {
        tomato::remove_message_loop();
    }

    WTL::CMessageLoop detail_m_impl;
};


} } // namespace pstade::tomato


inline
bool pstade_tomato_pre_translate_message(pstade::tomato::message_loop& loop, MSG& msg, pstade::overload)
{
    return pstade::tomato::pre_translate_message(loop.detail_m_impl, msg);
}


inline
bool pstade_tomato_on_idle(pstade::tomato::message_loop& loop, int count, pstade::overload)
{
    return pstade::tomato::on_idle(loop.detail_m_impl, count);
}


#endif
