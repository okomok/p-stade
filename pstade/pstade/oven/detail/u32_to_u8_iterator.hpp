#ifndef PSTADE_OVEN_DETAIL_U32_TO_U8_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_U32_TO_U8_ITERATOR_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


/*
 *
 * Copyright (c) 2004
 * John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */


#include "./prelude.hpp"
#include <boost/array.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/regex/pending/unicode_iterator.hpp>
#include "../read.hpp"
#include "./minimum_pure.hpp"


namespace pstade { namespace oven { namespace detail {


// The original iterator needs a little fix.


template< class Iterator, class U8Type >
struct u32_to_u8_iterator;


template< class Iterator, class U8Type >
struct u32_to_u8_iterator_super
{
    typedef
        boost::iterator_adaptor<
            u32_to_u8_iterator<Iterator, U8Type>,
            Iterator,
            U8Type,
            typename minimum_pure<
                boost::bidirectional_traversal_tag,
                typename boost::iterator_traversal<Iterator>::type
            >::type,
            U8Type const&
        >
    type;
};


template< class Iterator, class U8Type >
struct u32_to_u8_iterator :
    u32_to_u8_iterator_super<Iterator, U8Type>::type
{
private:
    typedef typename u32_to_u8_iterator_super<Iterator, U8Type>::type super_t;
    typedef typename super_t::reference ref_t;

    typedef typename boost::iterator_value<Iterator>::type base_value_t;
    BOOST_STATIC_ASSERT(sizeof(base_value_t)*CHAR_BIT == 32);
    BOOST_STATIC_ASSERT(sizeof(U8Type)*CHAR_BIT == 8);

public:
    explicit u32_to_u8_iterator()
    { }

    explicit u32_to_u8_iterator(Iterator it) :
        super_t(it), m_current(4)
    {
        m_values[0] = 0;
        m_values[1] = 0;
        m_values[2] = 0;
        m_values[3] = 0;
        m_values[4] = 0;
    }

template< class, class > friend struct u32_to_u8_iterator;
    template< class I >
    u32_to_u8_iterator(u32_to_u8_iterator<I, U8Type> const& other,
        typename boost::enable_if_convertible<I, Iterator>::type * = 0
    ) :
        super_t(other.base()), m_values(other.m_values), m_current(other.m_current)
    { }

private:
    mutable boost::array<U8Type, 5> m_values;
    mutable unsigned m_current;

    void extract_current() const
    {
        boost::uint32_t c = read(this->base());
        if (c > 0x10FFFFu)
            boost::detail::invalid_utf32_code_point(c);
        if (c < 0x80u) {
            m_values[0] = static_cast<unsigned char>(c);
            m_values[1] = static_cast<unsigned char>(0u);
            m_values[2] = static_cast<unsigned char>(0u);
            m_values[3] = static_cast<unsigned char>(0u);
        }
        else if (c < 0x800u) {
            m_values[0] = static_cast<unsigned char>(0xC0u + (c >> 6));
            m_values[1] = static_cast<unsigned char>(0x80u + (c & 0x3Fu));
            m_values[2] = static_cast<unsigned char>(0u);
            m_values[3] = static_cast<unsigned char>(0u);
        }
        else if (c < 0x10000u) {
            m_values[0] = static_cast<unsigned char>(0xE0u + (c >> 12));
            m_values[1] = static_cast<unsigned char>(0x80u + ((c >> 6) & 0x3Fu));
            m_values[2] = static_cast<unsigned char>(0x80u + (c & 0x3Fu));
            m_values[3] = static_cast<unsigned char>(0u);
        }
        else {
            m_values[0] = static_cast<unsigned char>(0xF0u + (c >> 18));
            m_values[1] = static_cast<unsigned char>(0x80u + ((c >> 12) & 0x3Fu));
            m_values[2] = static_cast<unsigned char>(0x80u + ((c >> 6) & 0x3Fu));
            m_values[3] = static_cast<unsigned char>(0x80u + (c & 0x3Fu));
        }
        m_current = 0;
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        if (m_current == 4)
            extract_current();
        return m_values[m_current];
    }

    template< class I >
    bool equal(u32_to_u8_iterator<I, U8Type> const& other) const
    {
        if (this->base() == other.base()) {
            // either the m_current's must be equal, or one must be 0 and 
            // the other 4: which means neither must have bits 1 or 2 set:
            return (m_current == other.m_current)
                || (((m_current | other.m_current) & 3) == 0);
        }
        return false;
    }

    void increment()
    {
        // if we have a pending read then read now, so that we know whether
        // to skip a position, or move to a low-surrogate:
        if (m_current == 4) {
            // pending read:
            extract_current();
        }
        // move to the next surrogate position:
        ++m_current;
        // if we've reached the end skip a position:
        if (m_values[m_current] == 0) {
            m_current = 4;
            ++this->base_reference();
        }
    }

    void decrement()
    {
        if ((m_current & 3) == 0) {
            --this->base_reference();
            extract_current();
            m_current = 3;
            while (m_current && (m_values[m_current] == 0))
                --m_current;
        }
        else
            --m_current;
    }
};


} } } // namespace pstade::oven::detail


#endif
