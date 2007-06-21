#ifndef PSTADE_OVEN_DETAIL_LINE_ITERATOR_HPP
#define PSTADE_OVEN_DETAIL_LINE_ITERATOR_HPP
#include "../prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> // find
#include <boost/assert.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_traits.hpp>
#include <boost/next_prior.hpp>
#include <pstade/enable_if.hpp>
#include <pstade/is_convertible.hpp>
#include "../iter_range.hpp"
#include "../reverse_iterator.hpp"
#include "./minimum_pure.hpp"


namespace pstade { namespace oven { namespace detail {


template< class ForwardIter >
struct line_iterator;


template< class ForwardIter >
struct line_iterator_super
{
    typedef
        boost::iterator_facade<
            line_iterator<ForwardIter>,
            iter_range<ForwardIter> const,
            typename minimum_pure<
                boost::bidirectional_traversal_tag,
                typename boost::iterator_traversal<ForwardIter>::type
            >::type
        >
    type;
};


template< class ForwardIter >
struct line_iterator :
    line_iterator_super<ForwardIter>::type
{
private:
    typedef typename line_iterator_super<ForwardIter>::type super_t;
    typedef typename super_t::value_type val_t;
    typedef typename boost::iterator_value<ForwardIter>::type base_val_t;

public:
    line_iterator()
    { }

    line_iterator(ForwardIter it, ForwardIter first, ForwardIter last, base_val_t delim) :
        m_first(first), m_last(last), m_delim(delim),
        m_line(it, std::find(it, last, delim))
    { }

    template< class F >
    line_iterator(line_iterator<F> const& other,
        typename enable_if< is_convertible<F, ForwardIter> >::type = 0
    ) :
        super_t(other.base()), m_first(other.begin()), m_last(other.end()), m_delim(other.delimiter()),
        m_line(other.line())
    { }

    ForwardIter begin() const
    {
        return m_first;
    }

    ForwardIter end() const
    {
        return m_last;
    }

    base_val_t delimiter() const
    {
        return m_delim;
    }

    val_t const& line() const
    {
        return m_line;
    }

private:
    ForwardIter m_first, m_last;
    base_val_t m_delim;
    val_t m_line; // [m_last, m_last) represents the end iterator.

    template< class Other >
    bool is_compatible(Other const& other) const
    {
        return m_last == other.end() && m_delim == other.delimiter();
    }

friend class boost::iterator_core_access;
    val_t const& dereference() const
    {
        return m_line;
    }

    template< class F >
    bool equal(line_iterator<F> const& other) const
    {
        BOOST_ASSERT(is_compatible(other));
        return m_line.begin() == other.line().begin();
    }

    void increment()
    {
        BOOST_ASSERT("out of range" && m_line.end() != m_last);
        ForwardIter it = boost::next(m_line.end());
        m_line.reset(it, std::find(it, m_last, m_delim));
    }

    void decrement()
    {
        BOOST_ASSERT("out of range" && m_line.begin() != m_first);
        ForwardIter it = boost::prior(m_line.begin());
        m_line.reset(std::find(make_reverse_iterator(it), make_reverse_iterator(m_first), m_delim).base(), it);
    }
};


} } } // namespace pstade::oven::detail


#endif
