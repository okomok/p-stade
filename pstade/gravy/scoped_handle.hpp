#ifndef PSTADE_GRAVY_SCOPED_HANDLE_HPP
#define PSTADE_GRAVY_SCOPED_HANDLE_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>
#include <pstade/nullptr.hpp>
#include <pstade/radish/bool_testable.hpp>
#include <pstade/verify.hpp>
#include "./sdk/windows.hpp"


namespace pstade { namespace gravy {


    namespace scoped_handle_detail {


        struct basic_impl :
            private boost::noncopyable
        {
            explicit basic_impl(HANDLE h) :
                m_h(h) 
            { }

            ~basic_impl()
            {
                pstade::verify( ::CloseHandle(m_h) );
            }

            HANDLE const m_h;
        };


        template< class NullHandle >
        struct basic :
            radish::bool_testable<basic<NullHandle>, boost::noncopyable>
        {
            explicit basic(HANDLE h = NullHandle::value())
            {
                reset(h);
            }

            void reset(HANDLE h = NullHandle::value())
            {
                m_pimpl.reset(h != NullHandle::value() ? new basic_impl(h) : PSTADE_NULLPTR);
            }

            HANDLE operator *() const
            {
                return m_pimpl->m_h;
            }

            HANDLE get() const
            {
                return m_pimpl ? m_pimpl->m_h : NullHandle::value();
            }

            operator radish::safe_bool() const
            {
                return radish::make_safe_bool(m_pimpl);
            }

        private:
            boost::scoped_ptr<basic_impl> m_pimpl;
        };


        // Note:
        // These cannot be static constants,
        // because these are defined as pointers.
        //
        struct NULL_handle
        {
            static HANDLE value() { return NULL; }
        };


        struct INVALID_handle
        {
            static HANDLE value() { return INVALID_HANDLE_VALUE; }
        };


    } // namespace scoped_handle_detail


    typedef
        scoped_handle_detail::basic<scoped_handle_detail::NULL_handle>
    scoped_nhandle;


    typedef
        scoped_handle_detail::basic<scoped_handle_detail::INVALID_handle>
    scoped_ihandle;


} } // namespace pstade::gravy


#endif
