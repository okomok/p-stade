#ifndef PSTADE_BISCUIT_RANGE_TOKEN_ITERATOR_HPP
#define PSTADE_BISCUIT_RANGE_TOKEN_ITERATOR_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iterator> // forward_iterator_tag
#include <boost/assert.hpp>
#include <boost/config.hpp> // BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE
#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/utility/addressof.hpp>
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
            boost::iterator_range<ForwardIter>,
            std::forward_iterator_tag, // forceful category
            boost::iterator_range<ForwardIter> const
        > type;
    };


} // namespace token_iterator_detail


template< class Parser, class ForwardIter, class UserState >
struct token_iterator :
    token_iterator_detail::super_<Parser, ForwardIter, UserState>::type
{
private:
    typedef typename token_iterator_detail::super_<Parser, ForwardIter, UserState>::type super_t;

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

    boost::iterator_range<ForwardIter> submatch() const { return m_submatch; }
    ForwardIter end() const { return m_last; }
    UserState& user_state() const { return *m_pus; }

private:
    boost::iterator_range<ForwardIter> m_submatch;
    ForwardIter m_last;
    UserState *m_pus;

    void search_submatch()
    {
        boost::iterator_range<ForwardIter> rng(boost::end(m_submatch), m_last);
        m_submatch = biscuit::search<Parser>(rng, *m_pus);
        // if not found, m_submatch becomes [m_last, m_last)
    }

friend class boost::iterator_core_access;
    typedef typename token_iterator_detail::super_<Parser, ForwardIter, UserState>::type super_t;

    void increment()
    {
        BOOST_ASSERT(boost::begin(m_submatch) != m_last && "out of range");

        search_submatch();
    }

    bool equal(token_iterator const& other) const
    {
        BOOST_ASSERT(m_last == other.m_last && m_pus == other.m_pus && "incompatible iterators");

        return escaped_iterator_range_equal(other);
    }

    typename super_t::reference dereference() const
    {
        return m_submatch;
    }

private:
    bool escaped_iterator_range_equal(token_iterator const& other) const
    {
        // 'operator==' of 'iterator_range' calls 'std::equal'!
        return m_submatch.equal(other.m_submatch);
    }
};


template< class Parser, class ForwardIter, class UserState > inline
token_iterator<Parser, ForwardIter, UserState>
make_token_iterator(ForwardIter const& x, ForwardIter const& last, UserState& us BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
{
    return token_iterator<Parser, ForwardIter, UserState>(x, last, us);
}


} } // namespace pstade::biscuit


#endif
