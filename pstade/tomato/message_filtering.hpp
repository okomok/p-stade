#ifndef PSTADE_TOMATO_MESSAGE_FILTERING_HPP
#define PSTADE_TOMATO_MESSAGE_FILTERING_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <pstade/apple/atl/module.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/apple/wtl/app.hpp> // CMessageFilter, CMessageLoop
#include <pstade/require.hpp>
#include <pstade/verify.hpp>


namespace pstade { namespace tomato {


namespace message_filtering_detail {


    struct impl
    {
        impl(WTL::CMessageFilter *pMessageFilter, DWORD dwThreadID) :
            m_pMessageFilter(pMessageFilter), m_dwThreadID(dwThreadID)
        {
            WTL::CMessageLoop *pLoop = _Module.GetMessageLoop(m_dwThreadID);
            PSTADE_REQUIRE( pLoop && pLoop->AddMessageFilter(m_pMessageFilter) );
        }

        ~impl()
        {
            WTL::CMessageLoop *pLoop = _Module.GetMessageLoop(m_dwThreadID);
            pstade::verify( pLoop && pLoop->RemoveMessageFilter(m_pMessageFilter) );
        }

    private:
        WTL::CMessageFilter *m_pMessageFilter;
        DWORD m_dwThreadID;
    };


} // namespace message_filtering_detail


struct message_filtering :
    private boost::noncopyable
{
    explicit message_filtering()
    { }
    
    explicit message_filtering(WTL::CMessageFilter *pMessageFilter, DWORD dwThreadID = ::GetCurrentThreadId())
    {
        start(pMessageFilter, dwThreadID);
    }

    void start(WTL::CMessageFilter *pMessageFilter, DWORD dwThreadID = ::GetCurrentThreadId())
    {
        m_pimpl.reset(new message_filtering_detail::impl(pMessageFilter, dwThreadID));
    }

    void stop()
    {
        m_pimpl.reset();
    }

private:
    boost::scoped_ptr<message_filtering_detail::impl> m_pimpl;
};


} } // namespace pstade::tomato


#endif
