#ifndef PSTADE_TOMATO_MESSAGE_FILTERING_HPP
#define PSTADE_TOMATO_MESSAGE_FILTERING_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <memory> // auto_ptr
#include <boost/microsoft/atl/module.hpp>
#include <boost/microsoft/sdk/windows.hpp>
#include <boost/microsoft/wtl/app.hpp> // CMessageFilter, CMessageLoop
#include <boost/noncopyable.hpp>
#include <pstade/require.hpp>


namespace pstade { namespace tomato {


namespace message_filtering_detail {


    struct impl :
        private boost::noncopyable
    {
        impl(WTL::CMessageFilter *pMessageFilter, DWORD dwThreadID) :
            m_pMessageFilter(pMessageFilter), m_dwThreadID(dwThreadID)
        {
            WTL::CMessageLoop *pLoop = _Module.GetMessageLoop(m_dwThreadID);
            PSTADE_REQUIRE(pLoop && pLoop->AddMessageFilter(m_pMessageFilter));
        }

        ~impl()
        {
            WTL::CMessageLoop *pLoop = _Module.GetMessageLoop(m_dwThreadID);
            PSTADE_REQUIRE(pLoop && pLoop->RemoveMessageFilter(m_pMessageFilter));
        }

    private:
        WTL::CMessageFilter *m_pMessageFilter;
        DWORD m_dwThreadID;
    };


} // namespace message_filtering_detail


struct message_filtering
{
    void start(WTL::CMessageFilter *pMessageFilter, DWORD dwThreadID = ::GetCurrentThreadId())
    {
        m_pimpl.reset(new message_filtering_detail::impl(pMessageFilter, dwThreadID));
    }

    void stop()
    {
        m_pimpl.reset();
    }

private:
    std::auto_ptr<message_filtering_detail::impl> m_pimpl;
};


} } // namespace pstade::tomato



#endif
