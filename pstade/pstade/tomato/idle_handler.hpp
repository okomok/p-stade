#ifndef PSTADE_TOMATO_IDLE_HANDLER_HPP
#define PSTADE_TOMATO_IDLE_HANDLER_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <memory> // auto_ptr
#include <boost/microsoft/atl/module.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <boost/microsoft/wtl/app.hpp> // CIdleHandler, CMessageLoop
#include <boost/noncopyable.hpp>
#include <pstade/derived_cast.hpp>
#include <pstade/require.hpp>


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
    virtual BOOL OnIdle()
    {
        DerivedT& d = pstade::derived(*this);
        return d.on_idle();
    }

// private:
    void detail_start(DWORD dwThreadID)
    {
        m_pimpl.reset(new idle_handler_detail::impl(this, dwThreadID));
    }

    void detail_stop()
    {
        m_pimpl.reset();
    }

private:
    std::auto_ptr<idle_handler_detail::impl> m_pimpl;
};


template< class DerivedT > inline
void start_idle_handler(idle_handler<DerivedT>& ih, DWORD dwThreadID = ::GetCurrentThreadId())
{
    ih.detail_start(dwThreadID);
}


template< class DerivedT > inline
void stop_idle_handler(idle_handler<DerivedT>& ih)
{
    ih.detail_stop();
}


} } // namespace pstade::tomato



#endif
