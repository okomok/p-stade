#ifndef PSTADE_GRAVY_WINDOW_TEXT_HPP
#define PSTADE_GRAVY_WINDOW_TEXT_HPP


// PStade.Gravy
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// A Random Access Readable Lvalue Range
// that represents a window text.


// Design:
//
// Other threads may change the text after calling '::GetWindowTextLength',
// so 'as_c_str' is still required.
// Note that there seems no way to know whether 'GetWindowText' was failed or empty.


#include <boost/assert.hpp>
#include <boost/range/begin.hpp>
#include <pstade/copy_construct.hpp>
#include <pstade/oven/array_range.hpp>
#include <pstade/oven/as_c_str.hpp>
#include <pstade/oven/distance.hpp>
#include <pstade/oven/iter_range.hpp>
#include "./sdk/tchar.hpp"
#include "./sdk/windows.hpp"
#include "./window_ref.hpp"


namespace pstade { namespace gravy {


    namespace window_text_detail {


        typedef
            oven::array_range<TCHAR>
        buffer_t;


        template<class = void>
        struct init
        {
            typedef init type;

            explicit init(window_ref wnd) :
                m_buf(1 + ::GetWindowTextLength(wnd))
            {
                ::GetWindowText(wnd,
                    boost::begin(m_buf), pstade::copy_construct<int>(oven::distance(m_buf)) );

                BOOST_ASSERT(oven::contains_zero(m_buf));
            }

        protected:
            buffer_t m_buf;
        };


        template<class = void>
        struct super_
        {
            typedef
                oven::iter_range<TCHAR const *>
            type;
        };


    } // namespace window_text_detail


    struct window_text :
        private window_text_detail::init<>::type,
        window_text_detail::super_<>::type
    {
    private:
        typedef window_text_detail::init<>::type init_t; 
        typedef window_text_detail::super_<>::type super_t;

    public:
        explicit window_text(window_ref wnd) :
            init_t(wnd),
            super_t(m_buf|oven::as_c_str)
        { }

        friend
        TCHAR const *pstade_gravy_c_str(window_text const& self)
        {
            return boost::begin(self.m_buf);
        }

    private:
        window_text(window_text const&);
        window_text& operator=(window_text const&);
    };


} } // namespace pstade::gravy


#endif
