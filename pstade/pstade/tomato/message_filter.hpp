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
        return d.pre_translate_message(pMsg);
    }

// private:
    void detail_start(DWORD dwThreadID)
    {
        m_pimpl.reset(new message_filter_detail::impl(this, dwThreadID));
    }

    void detail_stop()
    {
        m_pimpl.reset();
    }

private:
    std::auto_ptr<message_filter_detail::impl> m_pimpl;
};


template< class DerivedT > inline
void start_message_filter(message_filter<DerivedT>& mf, DWORD dwThreadID = ::GetCurrentThreadId())
{
    mf.detail_start(dwThreadID);
}


template< class DerivedT > inline
void stop_message_filter(message_filter<DerivedT>& mf)
{
    mf.detail_stop();
}


} } // namespace pstade::tomato



#endif
