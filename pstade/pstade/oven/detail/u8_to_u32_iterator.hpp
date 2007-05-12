#ifndef PSTADE_OVEN_DETAIL_U8_TO_U32_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_U8_TO_U32_ITERATOR_HPP


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


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/regex/pending/unicode_iterator.hpp>
#include "../advance_from.hpp"
#include "../read.hpp"
#include "./minimum_pure.hpp"


namespace pstade { namespace oven { namespace detail {


// The original iterator needs a little fix.


template< class ForwardIter, class U32Type >
struct u8_to_u32_iterator;


template< class ForwardIter, class U32Type >
struct u8_to_u32_iterator_super
{
    typedef
        boost::iterator_adaptor<
            u8_to_u32_iterator<ForwardIter, U32Type>,
            ForwardIter,
            U32Type,
            typename detail::minimum_pure<
                boost::bidirectional_traversal_tag,
                typename boost::iterator_traversal<ForwardIter>::type
            >::type,
            U32Type const&
        >
    type;
};


template< class ForwardIter, class U32Type >
struct u8_to_u32_iterator :
    u8_to_u32_iterator_super<ForwardIter, U32Type>::type
{
private:
    typedef typename u8_to_u32_iterator_super<ForwardIter, U32Type>::type super_t;
    typedef typename super_t::reference ref_t;

    // special values for pending iterator reads:
    BOOST_STATIC_CONSTANT(U32Type, pending_read = 0xffffffffu);

    typedef typename boost::iterator_value<ForwardIter>::type base_value_t;
    BOOST_STATIC_ASSERT(sizeof(base_value_t) * CHAR_BIT == 8);
    BOOST_STATIC_ASSERT(sizeof(U32Type) * CHAR_BIT == 32);

public:
    explicit u8_to_u32_iterator()
    { }

    explicit u8_to_u32_iterator(ForwardIter it) :
        super_t(it), m_value(pending_read)
    { }

template< class, class > friend struct u8_to_u32_iterator;
    template< class F >
    u8_to_u32_iterator(u8_to_u32_iterator<F, U32Type> const& other,
        typename boost::enable_if_convertible<F, ForwardIter>::type * = 0
    ) :
        super_t(other.base()), m_value(other.m_value)
    { }

private:
    mutable U32Type m_value;

    static void invalid_sequnce()
    {
        std::out_of_range e("Invalid UTF-8 sequence encountered while trying to encode UTF-32 character");
        boost::throw_exception(e);
    }

    void extract_current() const
    {
        m_value = static_cast<U32Type>(static_cast<boost::uint8_t>(read(this->base())));
        // we must not have a continuation character:
        if ((m_value & 0xC0u) == 0x80u)
            invalid_sequnce();
        // see how many extra byts we have:
        unsigned extra = boost::detail::utf8_trailing_byte_count(read(this->base()));
        // extract the extra bits, 6 from each extra byte:
        ForwardIter next = this->base();
        for (unsigned c = 0; c < extra; ++c) {
            ++next;
            m_value <<= 6;
            m_value += static_cast<boost::uint8_t>(read(next)) & 0x3Fu;
        }
        // we now need to remove a few of the leftmost bits, but how many depends
        // upon how many extra bytes we've extracted:
        static const boost::uint32_t masks[4] =
        {
            0x7Fu,
            0x7FFu,
            0xFFFFu,
            0x1FFFFFu,
        };
        m_value &= masks[extra];
        // check the result:
        if (m_value > static_cast<U32Type>(0x10FFFFu))
            invalid_sequnce();
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        if (m_value == pending_read)
            extract_current();
        return m_value;
    }

    void increment()
    {
        // skip high surrogate first if there is one:
        unsigned c = boost::detail::utf8_byte_count(read(this->base()));
        this->base_reference() = advance_from(this->base(), c);
        m_value = pending_read;
    }

    void decrement()
    {
        // Keep backtracking until we don't have a trailing character:
        unsigned count = 0;
        while ((read(--this->base_reference()) & 0xC0u) == 0x80u) ++count;
        // now check that the sequence was valid:
        if (count != boost::detail::utf8_trailing_byte_count(read(this->base())))
            invalid_sequnce();
        m_value = pending_read;
    }
};


} } } // namespace pstade::oven::detail


#endif
