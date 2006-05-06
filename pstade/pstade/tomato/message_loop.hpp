#ifndef PSTADE_TOMATO_MESSAGE_LOOP_HPP
#define PSTADE_TOMATO_MESSAGE_LOOP_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/microsoft/atl/module.hpp>
#include <boost/microsoft/wtl/app.hpp> // CMessageLoop
#include <pstade/require.hpp>


namespace pstade { namespace tomato {


struct message_loop
{
    message_loop()
    {
        PSTADE_REQUIRE(_Module.AddMessageLoop(&m_loop));
    }

    ~message_loop()
    {
        _Module.RemoveMessageLoop();
    }

    int run()
    {
        return m_loop.Run();
    }

private:
    WTL::CMessageLoop m_loop;
};


} } // namespace pstade::tomato


#endif
