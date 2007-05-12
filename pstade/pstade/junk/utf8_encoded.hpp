#ifndef PSTADE_OVEN_UTF8_ENCODED_HPP
#define PSTADE_OVEN_UTF8_ENCODED_HPP


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


#include <cstddef> // size_t
#include <sstream>
#include <stdexcept> // out_of_range
#include <boost/array.hpp>
#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/throw_exception.hpp>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include "./concepts.hpp"
#include "./detail/minimum_pure.hpp"
#include "./iter_range.hpp"
#include "./range_iterator.hpp"
#include "./read.hpp"


namespace pstade { namespace oven {


namespace utf8_encoded_detail {


    namespace here = utf8_encoded_detail;


    inline
    void invalid_utf32_code_point(boost::uint32_t val)
    {
       std::stringstream ss;
       ss << "Invalid UTF-32 code point U+"
           << std::showbase << std::hex << val
           << " encountered while trying to encode UTF-16 sequence";
       std::out_of_range e(ss.str());
       boost::throw_exception(e);
    }


    template< class U8Type >
    std::size_t u32_to_u8_copy(boost::uint32_t from, boost::array<U8Type, 4>& to)
    {
        std::size_t endIndex = 0;

        if (from > 0x10FFFFu)
            here::invalid_utf32_code_point(from);

        if (from < 0x80u) {
            to[endIndex++] = static_cast<unsigned char>(from);
        }
        else if (from < 0x800u) {
            to[endIndex++] = static_cast<unsigned char>(0xC0u + (from >> 6));
            to[endIndex++] = static_cast<unsigned char>(0x80u + (from & 0x3Fu));
        }
        else if (from < 0x10000u) {
            to[endIndex++] = static_cast<unsigned char>(0xE0u + (from >> 12));
            to[endIndex++] = static_cast<unsigned char>(0x80u + ((from >> 6) & 0x3Fu));
            to[endIndex++] = static_cast<unsigned char>(0x80u + (from & 0x3Fu));
        }
        else {
            to[endIndex++] = static_cast<unsigned char>(0xF0u + (from >> 18));
            to[endIndex++] = static_cast<unsigned char>(0x80u + ((from >> 12) & 0x3Fu));
            to[endIndex++] = static_cast<unsigned char>(0x80u + ((from >> 6) & 0x3Fu));
            to[endIndex++] = static_cast<unsigned char>(0x80u + (from & 0x3Fu));
        }

        BOOST_ASSERT(endIndex != 0);
        return endIndex;
    }


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
                typename detail::minimum_pure<
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
        BOOST_STATIC_ASSERT(sizeof(base_value_t) * CHAR_BIT == 32);
        BOOST_STATIC_ASSERT(sizeof(U8Type) * CHAR_BIT == 8);

    public:
        u32_to_u8_iterator()
        { }

        u32_to_u8_iterator(Iterator it, Iterator last) :
            super_t(it), m_last(last)
        {
            extract();
        }

    template< class, class > friend struct u32_to_u8_iterator;
        template< class I >
        u32_to_u8_iterator(u32_to_u8_iterator<I, U8Type> const& other,
            typename boost::enable_if_convertible<I, Iterator>::type * = 0
        ) :
            super_t(other.base()), m_values(other.m_values),
            m_curIndex(other.m_curIndex), m_endIndex(other.m_endIndex)
        { }

    private:
        Iterator m_last;
        boost::array<U8Type, 4> m_values;
        std::size_t m_curIndex, m_endIndex;

        void extract()
        {
            if (this->base() != m_last)
                m_endIndex = here::u32_to_u8_copy(read(this->base()), m_values);

            m_curIndex = 0;
        }

        template< class Other >
        bool is_compatible(Other const& other) const
        {
            return m_last == other.m_last;
        }

    friend class boost::iterator_core_access;
        ref_t dereference() const
        {
            return m_values[m_curIndex];
        }

        template< class I >
        bool equal(u32_to_u8_iterator<I, U8Type> const& other) const
        {
            BOOST_ASSERT(is_compatible(other));
            return this->base() == other.base() && m_curIndex == other.m_curIndex;
        }

        void increment()
        {
            ++m_curIndex;
            if (m_curIndex == m_endIndex) {
	            ++this->base_reference();
                extract();
            }
        }

        void decrement()
        {
            if (m_curIndex != 0)
	            --m_curIndex;
            else {
	            --this->base_reference();
	            m_endIndex = here::u32_to_u8_copy(read(this->base()), m_values);
                m_curIndex = m_endIndex - 1;
            }
        }
    };


} // namespace utf8_encoded_detail


template< class U8Type = boost::uint8_t >
struct op_make_utf8_encoded :
    callable< op_make_utf8_encoded<U8Type> >
{
    template< class Myself, class Range >
    struct apply
    {
        typedef
            utf8_encoded_detail::u32_to_u8_iterator<
                typename range_iterator<Range>::type,
                U8Type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        type;
    };

    template< class Result, class Range >
    Result call(Range& rng) const
    {
        PSTADE_CONCEPT_ASSERT((SinglePass<Range>));

        typedef typename Result::iterator iter_t;
        return Result(
            iter_t(boost::begin(rng), boost::end(rng)),
            iter_t(boost::end(rng),   boost::end(rng))
        );
    }
};


PSTADE_CONSTANT(make_utf8_encoded, (op_make_utf8_encoded<>))
PSTADE_PIPABLE(utf8_encoded, (op_make_utf8_encoded<>))


} } // namespace pstade::oven


#endif
