#ifndef PSTADE_TOMATO_WINDOW_CLASS_NAME_HPP
#define PSTADE_TOMATO_WINDOW_CLASS_NAME_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/array.hpp>
#include <boost/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/range/begin.hpp>
#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/integral_cast.hpp>
#include <pstade/oven/distance.hpp>
#include <pstade/oven/null_terminate_range.hpp>
#include <pstade/require.hpp>
#include "../diet/valid.hpp"


namespace pstade { namespace tomato {


namespace class_name_detail {


    typedef boost::array<TCHAR, 256>
    buffer_t;


    struct buffer_initer
    {
        buffer_initer(HWND hWnd)
        {
            BOOST_ASSERT(diet::valid(hWnd));

            PSTADE_REQUIRE(0 !=
                ::GetClassName( hWnd, boost::begin(m_buf), pstade::integral(oven::distance(m_buf)) )
            );

            BOOST_ASSERT(oven::is_null_terminated(m_buf));
        }

    protected:
        buffer_t m_buf;
    };


} // namespace class_name_detail


struct class_name :
    private class_name_detail::buffer_initer,
    oven::null_terminate_range<class_name_detail::buffer_t>,
    private boost::noncopyable
{
    typedef const TCHAR *const_iterator;
    typedef class_name pstade_tomato_cstringizable;

private:
    typedef class_name_detail::buffer_initer initer_t; 
    typedef oven::null_terminate_range<class_name_detail::buffer_t> super_t;

public:
    explicit class_name(HWND hWnd) :
        initer_t(hWnd),
        super_t(m_buf)
    { }

    const TCHAR *c_str() const
    { return boost::begin(m_buf); }

    const TCHAR *pstade_tomato_c_str() const
    { return c_str(); }
};


} } // namespace pstade::tomato


#endif
