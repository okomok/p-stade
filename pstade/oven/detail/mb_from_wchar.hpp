#ifndef PSTADE_OVEN_DETAIL_MB_FROM_WCHAR_HPP
#define PSTADE_OVEN_DETAIL_MB_FROM_WCHAR_HPP


// What:
//
// Fixed a bug that 'mb_from_wchar<>::value_type' was wrongly 'wchar_t'.
// Notice that 'boost::iterator_adaptor' can't fix this bug.


// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// mb_from_wchar.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com . 
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <cassert>
#include <cstddef> // size_t
#include <cstdlib> // for wctomb()

#include <boost/config.hpp> // for BOOST_DEDUCED_TYPENAME
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{ 
    using ::size_t; 
    using ::wctomb;
} // namespace std
#endif

#include <boost/pfto.hpp>
#include <boost/iterator/iterator_adaptor.hpp>

namespace pstade { namespace oven { namespace detail {

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// class used by text archives to translate wide strings and to char
// strings of the currently selected locale
template<class Base>    // the input iterator
class mb_from_wchar
    : public boost::iterator_adaptor<
        mb_from_wchar<Base>, 
        Base, // <fix>
        char, // </fix>
        boost::single_pass_traversal_tag,
        char
    >
{
    friend class boost::iterator_core_access;

    typedef BOOST_DEDUCED_TYPENAME boost::iterator_adaptor<
        mb_from_wchar<Base>, 
        Base, // <fix>
        char, // </fix>
        boost::single_pass_traversal_tag,
        char
    > super_t;

    typedef mb_from_wchar<Base> this_t;

    char dereference_impl() {
        if(! m_full){
            fill();
            m_full = true;
        }
        return m_buffer[m_bnext];
    }
    char dereference() const {
        return (const_cast<this_t *>(this))->dereference_impl();
    }

    // test for iterator equality
    bool equal(const mb_from_wchar<Base> & rhs) const {
        // once the value is filled, the base_reference has been incremented
        // so don't permit comparison anymore.
        return 
            0 == m_bend
            && 0 == m_bnext
            && this->base_reference() == rhs.base_reference()
        ;
    }

    void fill(){
        wchar_t value = * this->base_reference();
        #if (defined(__MINGW32__) && ((__MINGW32_MAJOR_VERSION > 3) \
        || ((__MINGW32_MAJOR_VERSION == 3) && (__MINGW32_MINOR_VERSION >= 8))))
        m_bend = std::wcrtomb(m_buffer, value, 0);
        #else
        m_bend = std::wctomb(m_buffer, value);
        #endif
        assert(-1 != m_bend);
        assert((std::size_t)m_bend <= sizeof(m_buffer));
        assert(m_bend > 0);
        m_bnext = 0;
    }

    void increment(){
        if(++m_bnext < m_bend)
            return;
        m_bend = 
        m_bnext = 0;
        ++(this->base_reference());
        m_full = false;
    }

    // buffer to handle pending characters
    int m_bend;
    int m_bnext;
    char m_buffer[9];
    bool m_full;

public:
    // <fix>
    explicit mb_from_wchar(Base start) :
        super_t(start),
    // </fix>
        m_bend(0),
        m_bnext(0),
        m_full(false)
    {}
    // intel 7.1 doesn't like default copy constructor
    mb_from_wchar(const mb_from_wchar & rhs) : 
        super_t(rhs.base_reference()),
        m_bend(rhs.m_bend),
        m_bnext(rhs.m_bnext),
        m_full(rhs.m_full)
    {}
};

} } } // namespace pstade::oven::detail


#endif
