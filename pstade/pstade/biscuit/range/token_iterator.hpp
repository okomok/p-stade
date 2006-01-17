#pragma once

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include <pstade/assert.hpp>
#include "../algorithm/search.hpp"

#include <pstade/workaround/warning_constant_condition_begin.hpp>

namespace pstade { namespace biscuit {


///////////////////////////////////////////////////////////////////////////////
// token_iterator
//
template< class Parser, class ForwardIter, class UserState >
struct token_iterator;


template< class Parser, class ForwardIter, class UserState >
struct token_iterator_super
{
	typedef boost::iterator_facade<
		token_iterator<Parser, ForwardIter, UserState>,
		boost::iterator_range<ForwardIter>,
		boost::forward_traversal_tag,
		boost::iterator_range<ForwardIter> // not reference!
	> type;
};


template< class Parser, class ForwardIter, class UserState >
struct token_iterator :
	token_iterator_super<Parser, ForwardIter, UserState>::type
{
	// structors
	token_iterator() : m_pus(0)
	{ }

	token_iterator(ForwardIter x, ForwardIter last, UserState *pus) :
		m_submatch(x, x), m_last(last), m_pus(pus)
	{
		search_submatch(); // trigger!
	}

	template< class ForwardIter2 >
	token_iterator(token_iterator<Parser, ForwardIter2, UserState> const& other) :
		m_submatch(other.submatch()), m_last(other.end()), m_pus(&other.user_state())
	{ }

	// accessors
	boost::iterator_range<ForwardIter> submatch() const { return m_submatch; }
	ForwardIter end() const { return m_last; }
	UserState& user_state() const { return *m_pus; }

private:
	boost::iterator_range<ForwardIter> m_submatch;
	ForwardIter m_last;
	UserState *m_pus;

	void search_submatch()
	{
		// get a submatch
		boost::iterator_range<ForwardIter> rng(boost::end(m_submatch), m_last);
		m_submatch = biscuit::search<Parser>(rng, *m_pus);
		// if not found, m_submatch becomes [m_last, m_last)
	}

	// for iterator_facade
	friend class boost::iterator_core_access;

	void increment()
	{
		PSTADE_ASSERT(boost::begin(m_submatch) != m_last && "pstade::biscuit::token_iterator - out of range.");

		search_submatch();
	}

	bool equal(token_iterator const& other) const
	{
		PSTADE_ASSERT(m_last == other.m_last && m_pus == other.m_pus && "pstade::biscuit::token_iterator - incompatible iterators are compared");

		return m_submatch == other.m_submatch;
	}

	boost::iterator_range<ForwardIter> dereference() const
	{
	#if !BOOST_WORKAROUND(BOOST_MSVC, < 1300)
		return m_submatch;
	#else
		// See: insert_backref_pfto at "../match_results/match_results.hpp"
		return const_cast< boost::iterator_range<ForwardIter>& >(m_submatch);
	#endif // !BOOST_WORKAROUND(BOOST_MSVC, < 1300)
	}
};


///////////////////////////////////////////////////////////////////////////////
// make_token_iterator
//
template< class Parser, class ForwardIter, class UserState > inline
token_iterator<Parser, ForwardIter, UserState>
make_token_iterator(ForwardIter x, ForwardIter last, UserState *pus BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(Parser))
{
	return token_iterator<Parser, ForwardIter, UserState>(x, last, pus);
}


} } // namespace pstade::biscuit

#include <pstade/workaround/warning_constant_condition_end.hpp>
