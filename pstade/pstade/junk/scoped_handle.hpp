#ifndef PSTADE_TOMATO_SCOPED_HANDLE_HPP
#define PSTADE_TOMATO_SCOPED_HANDLE_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/noncopyable.hpp>
#include <pstade/apple/sdk/windows.hpp>


namespace pstade { namespace tomato {


namespace scoped_handle_detail {


    template< class NullHandle >
    struct basic :
        boost::noncopyable
    {
    private:
        typedef basic self_t;

    public:
        explicit basic(HANDLE h = NullHandle::value()) :
            m_h(h) 
        { }

        ~basic()
        {
            if (is_valid()) {
                BOOL ok = ::CloseHandle(m_h);
                BOOST_ASSERT(ok);
            }
        }

        void reset(HANDLE h = NullHandle::value())
        {
            BOOST_ASSERT(h == NullHandle::value() || h != m_h);
            self_t(h).swap(*this);
        }

        HANDLE operator*() const
        {
            BOOST_ASSERT(is_valid());
            return m_h;
        }

        HANDLE get() const
        {
            return m_h;
        }

        void swap(self_t& other)
        {
            HANDLE h = other.m_h;
            other.m_h = m_h;
            m_h = h;
        }

        operator bool() const
        {
            return is_valid();
        }

        bool is_valid() const
        {
            return m_h != NullHandle::value();
        }

    private:
        HANDLE m_h;
    };


    struct NULL_handle
    {
        static HANDLE value() { return NULL; }
    };


    struct INVALID_handle
    {
        static HANDLE value() { return INVALID_HANDLE_VALUE; }
    };


} // namespace scoped_handle_detail


typedef scoped_handle_detail::basic<scoped_handle_detail::NULL_handle>
scoped_nhandle;


typedef scoped_handle_detail::basic<scoped_handle_detail::INVALID_handle>
scoped_ihandle;


} } // namespace pstade::tomato


#endif
