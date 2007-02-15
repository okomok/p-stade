#ifndef PSTADE_OVEN_DETAIL_INDEXED_DEQUE_HPP
#define PSTADE_OVEN_DETAIL_INDEXED_DEQUE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <deque>
#include <boost/assert.hpp>


namespace pstade { namespace oven { namespace detail {


template< class Value >
struct indexed_deque
{
    typedef std::deque<Value> deque_t;
    typedef Value value_type;
    typedef typename deque_t::difference_type index_type;

    void positive_push(value_type const& v)
    {
        m_positive.push_back(v);
    }

    void negative_push(value_type const& v)
    {
        m_negative.push_back(v);
    }

    value_type const& operator[](index_type const& i) const
    {
        BOOST_ASSERT(is_in_range(i));

        if (i >= 0)
            return *(m_positive.begin() + i);
        else
            return *(m_negative.begin() + (-i-1));
    }

    bool is_in_range(index_type const& i) const
    {
        if (i >= 0)
            return i < (m_positive.end() - m_positive.begin());
        else
            return (-i) <= (m_negative.end() - m_negative.begin());
    }

private:
    deque_t m_positive;
    deque_t m_negative;
};


} } } // namespace pstade::oven::detail


#endif
