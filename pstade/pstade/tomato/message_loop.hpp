#ifndef PSTADE_TOMATO_MESSAGE_LOOP_HPP
#define PSTADE_TOMATO_MESSAGE_LOOP_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/atl/module.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/apple/wtl/app.hpp> // CMessageLoop
#include <pstade/require.hpp>
#include <pstade/verify.hpp>


namespace pstade { namespace tomato {


namespace message_loop_detail {


    inline
    void create_message_queue()
    {
        MSG msg;
        ::PeekMessage(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);
    }


} // namespace message_loop_detail


struct message_loop
{
    message_loop()
    {
        PSTADE_REQUIRE( _Module.AddMessageLoop(&m_loop) );
    }

    ~message_loop()
    {
        pstade::verify( _Module.RemoveMessageLoop() );
    }

    int run()
    {
        message_loop_detail::create_message_queue();
        return m_loop.Run();
    }

private:
    WTL::CMessageLoop m_loop;
};


} } // namespace pstade::tomato


#endif
