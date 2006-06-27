#ifndef PSTADE_TOMATO_WINDOW_WINDOW_TEXT_HPP
#define PSTADE_TOMATO_WINDOW_WINDOW_TEXT_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Model of:
//
// RandomAccessRange of TCHAR


// See:
//
// boost::base_from_member


// Design:
//
// Other threads may change the text after calling '::GetWindowTextLength',
// so 'null_terminate_range' is still required.
// Note that there seems no way to know whether 'GetWindowText' was failed or empty.


#include <boost/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/range/begin.hpp>
#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/oven/array_range.hpp>
#include <pstade/oven/distance.hpp>
#include <pstade/oven/null_terminate_range.hpp>
#include "../diet/valid.hpp"


namespace pstade { namespace tomato {


namespace window_text_detail {


    typedef oven::array_range<TCHAR>
    buffer_t;


    struct buffer_init
    {
        buffer_init(HWND hWnd) :
            m_buf(1 + ::GetWindowTextLength(hWnd))
        {
            BOOST_ASSERT(diet::valid(hWnd));

            ::GetWindowText(hWnd,
                boost::begin(m_buf), oven::distance(m_buf)
            );

            BOOST_ASSERT(oven::is_null_terminated(m_buf));
        }

    protected:
        buffer_t m_buf;
    };


} // namespace window_text_detail


struct window_text :
    private window_text_detail::buffer_init,
    oven::null_terminate_range<window_text_detail::buffer_t>,
    private boost::noncopyable
{
    typedef const TCHAR *const_iterator; // :-)
    typedef window_text pstade_tomato_cstringizable;

private:
    typedef window_text_detail::buffer_init init_t; 
    typedef oven::null_terminate_range<window_text_detail::buffer_t> super_t;

public:
    explicit window_text(HWND hWnd) :
        init_t(hWnd),
        super_t(m_buf)
    { }

    const TCHAR *c_str() const
    { return boost::begin(m_buf); }

    const TCHAR *pstade_tomato_c_str() const
    { return c_str(); }
};


} } // namespace pstade::tomato


#endif
