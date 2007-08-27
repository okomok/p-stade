#ifndef PSTADE_OVEN_DETAIL_U16_TO_U32_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_U16_TO_U32_ITERATOR_HPP
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


#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/regex/pending/unicode_iterator.hpp>
#include "../read.hpp"
#include "./minimum_pure.hpp"


namespace pstade { namespace oven { namespace detail {


// The original iterator needs a little fix.


template< class ForwardIter, class U32Type >
struct u16_to_u32_iterator;


template< class ForwardIter, class U32Type >
struct u16_to_u32_iterator_super
{
    typedef
        boost::iterator_adaptor<
            u16_to_u32_iterator<ForwardIter, U32Type>,
            ForwardIter,
            U32Type const,
            typename minimum_pure<
                boost::bidirectional_traversal_tag,
                typename boost::iterator_traversal<ForwardIter>::type
            >::type
        >
    type;
};


template< class ForwardIter, class U32Type >
struct u16_to_u32_iterator :
    u16_to_u32_iterator_super<ForwardIter, U32Type>::type
{
private:
    typedef typename u16_to_u32_iterator_super<ForwardIter, U32Type>::type super_t;
    typedef typename super_t::reference ref_t;

    // special values for pending iterator reads:
    BOOST_STATIC_CONSTANT(U32Type, pending_read = 0xffffffffu);

    typedef typename boost::iterator_value<ForwardIter>::type base_value_type;
    BOOST_STATIC_ASSERT(sizeof(base_value_type)*CHAR_BIT == 16);
    BOOST_STATIC_ASSERT(sizeof(U32Type)*CHAR_BIT == 32);

public:
    explicit u16_to_u32_iterator()
    { }

    explicit u16_to_u32_iterator(ForwardIter it) :
        super_t(it), m_value(pending_read)
    { }

template< class, class > friend struct u16_to_u32_iterator;
    template< class F >
    u16_to_u32_iterator(u16_to_u32_iterator<F, U32Type> const& other,
        typename boost::enable_if_convertible<F, ForwardIter>::type * = 0
    ) :
        super_t(other.base()), m_value(other.m_value)
    { }

private:
    mutable U32Type m_value;

    static void invalid_code_point(boost::uint16_t val)
    {
#ifndef BOOST_NO_STD_LOCALE
        std::stringstream ss;
        ss << "Misplaced UTF-16 surrogate U+" << std::showbase << std::hex << val << " encountered while trying to encode UTF-32 sequence";
        std::out_of_range e(ss.str());
#else
        std::out_of_range e("Misplaced UTF-16 surrogate encountered while trying to encode UTF-32 sequence");
#endif
        boost::throw_exception(e);
    }

    void extract_current() const
    {
        namespace detail = boost::detail;

        m_value = static_cast<U32Type>(static_cast<boost::uint16_t>(read(this->base())));
        // if the last value is a high surrogate then adjust this->base() and m_value as needed:
        if (detail::is_high_surrogate(read(this->base()))) {
            // precondition; next value must have be a low-surrogate:
            ForwardIter next(this->base());
            boost::uint16_t t = read(++next);
            if ((t & 0xFC00u) != 0xDC00u)
                invalid_code_point(t);
            m_value = (m_value - detail::high_surrogate_base) << 10;
            m_value |= (static_cast<U32Type>(static_cast<boost::uint16_t>(t)) & detail::ten_bit_mask);
        }
        // postcondition; result must not be a surrogate:
        if (detail::is_surrogate(m_value))
            invalid_code_point(static_cast<boost::uint16_t>(m_value));
    }

friend class boost::iterator_core_access;
    ref_t dereference()const
    {
        if (m_value == pending_read)
            extract_current();
        return m_value;
    }

    template< class F >
    bool equal(u16_to_u32_iterator<F, U32Type> const& other) const
    {
        return this->base() == other.base();
    }

    void increment()
    {
        // skip high surrogate first if there is one:
        if (boost::detail::is_high_surrogate(read(this->base()))) ++this->base_reference();
        ++this->base_reference();
        m_value = pending_read;
    }

    void decrement()
    {
        --this->base_reference();
        // if we have a low surrogate then go back one more:
        if (boost::detail::is_low_surrogate(read(this->base()))) 
            --this->base_reference();
        m_value = pending_read;
    }
};


} } } // namespace pstade::oven::detail


#endif
