#ifndef PSTADE_TOMATO_IDLE_HANDLING_HPP
#define PSTADE_TOMATO_IDLE_HANDLING_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <pstade/apple/atl/module.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/apple/wtl/app.hpp> // CIdleHandler, CMessageLoop
#include <pstade/require.hpp>
#include <pstade/verify.hpp>


namespace pstade { namespace tomato {


namespace idle_handling_detail {


    struct impl
    {
        impl(WTL::CIdleHandler *pIdleHandler, DWORD dwThreadID) :
            m_pIdleHandler(pIdleHandler), m_dwThreadID(dwThreadID)
        {
            WTL::CMessageLoop *pLoop = _Module.GetMessageLoop(m_dwThreadID);
            PSTADE_REQUIRE( pLoop && pLoop->AddIdleHandler(m_pIdleHandler) );
        }

        ~impl()
        {
            WTL::CMessageLoop *pLoop = _Module.GetMessageLoop(m_dwThreadID);
            PSTADE_VERIFY( pLoop && pLoop->RemoveIdleHandler(m_pIdleHandler) );
        }

    private:
        WTL::CIdleHandler *m_pIdleHandler;
        DWORD m_dwThreadID;
    };


} // namespace idle_handling_detail


struct idle_handling :
    private boost::noncopyable
{
    explicit idle_handling()
    { }

    explicit idle_handling(WTL::CIdleHandler *pIdleHandler, DWORD dwThreadID = ::GetCurrentThreadId())
    {
        start(pIdleHandler, dwThreadID);
    }

    void start(WTL::CIdleHandler *pIdleHandler, DWORD dwThreadID = ::GetCurrentThreadId())
    {
        m_pimpl.reset(new idle_handling_detail::impl(pIdleHandler, dwThreadID));
    }

    void stop()
    {
        m_pimpl.reset();
    }

private:
    boost::scoped_ptr<idle_handling_detail::impl> m_pimpl;
};


} } // namespace pstade::tomato


#endif
