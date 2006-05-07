#ifndef PSTADE_TOMATO_MESSAGE_FILTER_HPP
#define PSTADE_TOMATO_MESSAGE_FILTER_HPP


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
#include <pstade/derived_cast.hpp>
#include <pstade/require.hpp>
#include "./access.hpp"


namespace pstade { namespace tomato {


namespace message_filter_detail {


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


} // namespace message_filter_detail


template< class DerivedT >
struct message_filter :
    WTL::CMessageFilter,
    private boost::noncopyable
{
    virtual BOOL PreTranslateMessage(MSG *pMsg)
    {
        DerivedT& d = pstade::derived(*this);
        return access::detail_pre_translate_message(d, pMsg);
    }

    void start_message_filter(DWORD dwThreadID = ::GetCurrentThreadId())
    {
        m_pimpl.reset(new message_filter_detail::impl(this, dwThreadID));
    }

    void stop_message_filter()
    {
        m_pimpl.reset();
    }

private:
    std::auto_ptr<message_filter_detail::impl> m_pimpl;
};


} } // namespace pstade::tomato



#endif
