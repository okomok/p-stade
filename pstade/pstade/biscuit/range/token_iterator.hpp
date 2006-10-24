#ifndef PSTADE_BISCUIT_RANGE_TOKEN_ITERATOR_HPP
#define PSTADE_BISCUIT_RANGE_TOKEN_ITERATOR_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/iterator/iterator_categories.hpp> // forward_traversal_tag
#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/utility/addressof.hpp>
#include <pstade/oven/iter_range.hpp>
#include "../algorithm/search.hpp"


namespace pstade { namespace biscuit {


template< class Parser, class ForwardIter, class UserState >
struct token_iterator;


namespace token_iterator_detail {


    template< class Parser, class ForwardIter, class UserState >
    struct super_
    {
        typedef boost::iterator_facade<
            token_iterator<Parser, ForwardIter, UserState>,
            oven::iter_range<ForwardIter> const,
            boost::forward_traversal_tag
        > type;
    };


} // namespace token_iterator_detail


template< class Parser, class ForwardIter, class UserState >
struct token_iterator :
    token_iterator_detail::super_<Parser, ForwardIter, UserState>::type
{
private:
    typedef typename token_iterator_detail::super_<Parser, ForwardIter, UserState>::type super_t;
    typedef typename super_t::reference ref_t;

public:
    token_iterator()
    { }

    token_iterator(ForwardIter const& x, ForwardIter const& last, UserState& us) :
        m_submatch(x, x), m_last(last),
        m_pus(boost::addressof(us))
    {
        search_submatch(); // trigger!
    }

    template< class ForwardIter_ >
    token_iterator(
        token_iterator<Parser, ForwardIter_, UserState> const& other,
        typename boost::enable_if_convertible<ForwardIter_, ForwardIter>::type * = 0
    ) :
        super_t(other.base()), m_submatch(other.submatch()), m_last(other.end()),
        m_pus( boost::addressof(other.user_state()) )
    { }

    oven::iter_range<ForwardIter> const& submatch() const
    {
        return m_submatch;
    }

    ForwardIter const& end() const
    {
        return m_last;
    }

    UserState& user_state() const
    {
        return *m_pus;
    }

private:
    oven::iter_range<ForwardIter> m_submatch;
    ForwardIter m_last;
    UserState *m_pus;

    void search_submatch()
    {
        oven::iter_range<ForwardIter> rng(boost::end(m_submatch), m_last);
        m_submatch = biscuit::search<Parser>(rng, *m_pus);
        // if not found, m_submatch becomes [m_last, m_last)
    }

    template< class OtherIter >
    bool is_compatible(OtherIter const& other) const
    {
        return m_last == other.m_last && m_pus == other.m_pus;
    }

friend class boost::iterator_core_access;
    ref_t dereference() const
    {
        return m_submatch;
    }

    template< class OtherIter >
    bool equal(OtherIter const& other) const
    {
        BOOST_ASSERT(is_compatible(other));
        return m_submatch == other.submatch();
    }

    void increment()
    {
        BOOST_ASSERT("out of range" && boost::begin(m_submatch) != m_last);
        search_submatch();
    }
};


template< class Parser, class ForwardIter, class UserState > inline
token_iterator<Parser, ForwardIter, UserState> const
make_token_iterator(ForwardIter const& x, ForwardIter const& last, UserState& us)
{
    return token_iterator<Parser, ForwardIter, UserState>(x, last, us);
}


} } // namespace pstade::biscuit


#endif
