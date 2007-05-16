#ifndef PSTADE_TOMATO_IDLE_HANDLER_HPP
#define PSTADE_TOMATO_IDLE_HANDLER_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <memory> // auto_ptr
#include <boost/noncopyable.hpp>
#include <pstade/apple/atl/module.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/apple/wtl/app.hpp> // CIdleHandler, CMessageLoop
#include <pstade/derived_cast.hpp>
#include <pstade/require.hpp>
#include "./access.hpp"


namespace pstade { namespace tomato {


namespace idle_handler_detail {


    struct impl :
        private boost::noncopyable
    {
        impl(WTL::CIdleHandler *pIdleHandler, DWORD dwThreadID) :
            m_pIdleHandler(pIdleHandler), m_dwThreadID(dwThreadID)
        {
            WTL::CMessageLoop *pLoop = _Module.GetMessageLoop(m_dwThreadID);
            PSTADE_REQUIRE(pLoop && pLoop->AddIdleHandler(m_pIdleHandler));
        }

        ~impl()
        {
            WTL::CMessageLoop *pLoop = _Module.GetMessageLoop(m_dwThreadID);
            PSTADE_REQUIRE(pLoop && pLoop->RemoveIdleHandler(m_pIdleHandler));
        }

    private:
        WTL::CIdleHandler *m_pIdleHandler;
        DWORD m_dwThreadID;
    };


} // namespace idle_handler_detail


template< class DerivedT >
struct idle_handler :
    WTL::CIdleHandler,
    private boost::noncopyable
{
    BOOL OnIdle() // override
    {
        DerivedT& d = pstade::derived(*this);
        return access::detail_on_idle(d);
    }

    void start_idle_handler(DWORD dwThreadID = ::GetCurrentThreadId())
    {
        m_pimpl.reset(new idle_handler_detail::impl(this, dwThreadID));
    }

    void stop_idle_handler()
    {
        m_pimpl.reset();
    }

private:
    std::auto_ptr<idle_handler_detail::impl> m_pimpl;
};


} } // namespace pstade::tomato



#endif
