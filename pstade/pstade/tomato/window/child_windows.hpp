#ifndef PSTADE_TOMATO_WINDOW_CHILD_WINDOWS_HPP
#define PSTADE_TOMATO_WINDOW_CHILD_WINDOWS_HPP


// PStade.Tomato
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Model of:
//
// Sausage.Generator of child windows.


#include <boost/assert.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/apple/sdk/windows.hpp>
#include "./window_ptr.hpp"


namespace pstade { namespace tomato {


namespace child_windows_detail {


    template< class Yield >
    BOOL CALLBACK proc(HWND hWnd, LPARAM lParam)
    {
        BOOST_ASSERT(::IsWindow(hWnd));

        try {
            Yield& yield = *reinterpret_cast<Yield *>(lParam);
            yield(hWnd);
            return TRUE;
        }
        catch (...) { // never propagate.
            return FALSE;
        }
    }


    template< class Yield > inline
    void generate(window_ptr parent, Yield yield)
    {
        // Note:
        // if no child, EnumChildWindows "fails"
        // and the GetLastError value is undocumented.
        // So there seems no way to know whether or not
        // api failed.
        ::EnumChildWindows(
            parent.get(),
            &proc<Yield>,
            reinterpret_cast<LPARAM>(boost::addressof(yield))
        );
    }


} // namespace child_windows_detail


struct child_windows
{
    // 'NULL' means the root window.
    explicit child_windows(window_ptr parent) :
        m_parent(parent)
    { }

    typedef HWND result_type;

    template< class Yield >
    void operator()(Yield yield) const
    {
        child_windows_detail::generate(m_parent, yield);
    }

    HWND parent() const
    {
        return m_parent.get();
    }

private:
    window_ptr m_parent;
};


} } // namespace pstade::tomato


#endif
