#ifndef PSTADE_TOMATO_WINDOW_CLASS_NAME_HPP
#define PSTADE_TOMATO_WINDOW_CLASS_NAME_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// A Random Access Traversal Readable Lvalue Range
// that represents a window class name.


#include <boost/array.hpp>
#include <boost/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/range/begin.hpp>
#include <pstade/apple/sdk/tchar.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include <pstade/oven/null_terminate_range.hpp>
#include <pstade/require.hpp>
#include <pstade/static_c.hpp>
#include "../access.hpp"
#include "../diet/valid.hpp"


namespace pstade { namespace tomato {


namespace class_name_detail {


    typedef static_c<std::size_t, 256>
    buffer_size;

    typedef boost::array<TCHAR, buffer_size::value>
    buffer_t;


    template< class = void >
    struct init
    {
        typedef init type;

        explicit init(HWND hWnd)
        {
            BOOST_ASSERT(diet::valid(hWnd));

            PSTADE_REQUIRE(0 !=
                ::GetClassName(hWnd, boost::begin(m_buf), buffer_size::value)
            );

            BOOST_ASSERT(oven::is_null_terminated(m_buf));
        }

    protected:
        buffer_t m_buf;
    };


    template< class = void >
    struct super_
    {
        typedef oven::null_terminate_range<
            class_name_detail::buffer_t const // constant range!
        > type;
    };


} // namespace class_name_detail


struct class_name :
    private class_name_detail::init<>::type,
    class_name_detail::super_<>::type,
    private boost::noncopyable
{
    typedef class_name pstade_tomato_cstringizable;

private:
    typedef class_name_detail::init<>::type init_t; 
    typedef class_name_detail::super_<>::type super_t;

public:
    explicit class_name(HWND hWnd) :
        init_t(hWnd),
        super_t(m_buf)
    { }

private:
friend class access;
    TCHAR const *pstade_tomato_c_str() const
    {
        return boost::begin(m_buf);
    }
};


} } // namespace pstade::tomato


#endif
