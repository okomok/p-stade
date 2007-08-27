#ifndef PSTADE_OVEN_DETAIL_U32_TO_U16_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_U32_TO_U16_ITERATOR_HPP
#include "./prefix.hpp"


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


#include <boost/array.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/regex/pending/unicode_iterator.hpp>
#include "../read.hpp"
#include "./minimum_pure.hpp"


namespace pstade { namespace oven { namespace detail {


// The original iterator needs a little fix.


template< class Iterator, class U16Type >
struct u32_to_u16_iterator;


template< class Iterator, class U16Type >
struct u32_to_u16_iterator_super
{
    typedef
        boost::iterator_adaptor<
            u32_to_u16_iterator<Iterator, U16Type>,
            Iterator,
            U16Type const,
            typename minimum_pure<
                boost::bidirectional_traversal_tag,
                typename boost::iterator_traversal<Iterator>::type
            >::type
        >
    type;
};


template< class Iterator, class U16Type >
struct u32_to_u16_iterator :
    u32_to_u16_iterator_super<Iterator, U16Type>::type
{
private:
    typedef typename u32_to_u16_iterator_super<Iterator, U16Type>::type super_t;
    typedef typename super_t::reference ref_t;

    typedef typename boost::iterator_value<Iterator>::type base_value_type;
    BOOST_STATIC_ASSERT(sizeof(base_value_type)*CHAR_BIT == 32);
    BOOST_STATIC_ASSERT(sizeof(U16Type)*CHAR_BIT == 16);

public:
    explicit u32_to_u16_iterator()
    { }

    explicit u32_to_u16_iterator(Iterator it) :
        super_t(it), m_current(2)
    {
        m_values[0] = 0;
        m_values[1] = 0;
        m_values[2] = 0;
    }

template< class, class > friend struct u32_to_u16_iterator;
    template< class I >
    u32_to_u16_iterator(u32_to_u16_iterator<I, U16Type> const& other,
        typename boost::enable_if_convertible<I, Iterator>::type * = 0
    ) :
        super_t(other.base()), m_values(other.m_values), m_current(other.m_current)
    { }

private:
    mutable U16Type m_values[3];
    mutable unsigned m_current;

    void extract_current() const
    {
        namespace detail = boost::detail;

        // begin by checking for a code point out of range:
        boost::uint32_t v = read(this->base());
        if (v >= 0x10000u) {
            if (v > 0x10FFFFu)
                detail::invalid_utf32_code_point(read(this->base()));
            // split into two surrogates:
            m_values[0] = static_cast<U16Type>(v >> 10) + detail::high_surrogate_base;
            m_values[1] = static_cast<U16Type>(v & detail::ten_bit_mask) + detail::low_surrogate_base;
            m_current = 0;
            BOOST_ASSERT(detail::is_high_surrogate(m_values[0]));
            BOOST_ASSERT(detail::is_low_surrogate(m_values[1]));
        }
        else {
            // 16-bit code point:
            m_values[0] = static_cast<U16Type>(read(this->base()));
            m_values[1] = 0;
            m_current = 0;
            // value must not be a surrogate:
            if (detail::is_surrogate(m_values[0]))
                detail::invalid_utf32_code_point(read(this->base()));
        }
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        if (m_current == 2)
            extract_current();
        return m_values[m_current];
    }

    template< class I >
    bool equal(u32_to_u16_iterator<I, U16Type> const& other) const
    {
        if (this->base() == other.base()) {
            // Both m_currents must be equal, or both even
            // this is the same as saying their sum must be even:
            return (m_current + other.m_current) & 1u ? false : true;
        }
        return false;
    }

    void increment()
    {
        // if we have a pending read then read now, so that we know whether
        // to skip a position, or move to a low-surrogate:
        if (m_current == 2) {
            // pending read:
            extract_current();
        }
        // move to the next surrogate position:
        ++m_current;
        // if we've reached the end skip a position:
        if (m_values[m_current] == 0) {
            m_current = 2;
            ++this->base_reference();
        }
    }

    void decrement()
    {
        if (m_current != 1) {
            // decrementing an iterator always leads to a valid position:
            --this->base_reference();
            extract_current();
            m_current = m_values[1] ? 1 : 0;
        }
        else {
            m_current = 0;
        }
    }
};


} } } // namespace pstade::oven::detail


#endif
