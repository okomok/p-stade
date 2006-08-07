#ifndef PSTADE_TOMATO_SCOPED_FILE_VIEW_HPP
#define PSTADE_TOMATO_SCOPED_FILE_VIEW_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/nullptr.hpp>
#include <pstade/verify.hpp>


namespace pstade { namespace tomato {


namespace scoped_file_view_detail {


    struct impl :
        private boost::noncopyable
    {
        explicit impl(LPVOID pView) :
            m_pView(pView)
        {
            BOOST_ASSERT( m_pView != NULL );
        }

        ~impl()
        {
            pstade::verify( ::UnmapViewOfFile(m_pView) );
        }

        const LPVOID m_pView;
    };


} // namespace scoped_file_view_detail


struct scoped_file_view :
    private boost::noncopyable
{
    explicit scoped_file_view(LPVOID pView = NULL)
    {
        reset(pView);
    }

    void reset(LPVOID pView = NULL)
    {
        m_pimpl.reset(pView != NULL ? new scoped_file_view_detail::impl(pView) : PSTADE_NULLPTR);
    }

    LPVOID operator*() const
    {
        return m_pimpl->m_pView;
    }

    LPVOID get() const
    {
        return m_pimpl ? m_pimpl->m_pView : NULL;
    }

    operator bool() const
    {
        return m_pimpl;
    }

private:
    boost::scoped_ptr<scoped_file_view_detail::impl> m_pimpl;
};


} } // namespace pstade::tomato


#endif
