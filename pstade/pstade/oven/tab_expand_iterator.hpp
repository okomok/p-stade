#pragma once

#include <algorithm>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_traits.hpp> // for iterator_value
#include <boost/type_traits/add_const.hpp>

#if !defined(PSTADE_OVEN_TAB_EXPAND_DEBUG_MODE)
	#define PSTADE_OVEN_TAB_EXPAND_SPACE ' '
	#define PSTADE_OVEN_TAB_EXPAND_TAB '\t'
#else
	#define PSTADE_OVEN_TAB_EXPAND_SPACE 'S'
	#define PSTADE_OVEN_TAB_EXPAND_TAB 'T'
#endif

namespace pstade { namespace oven {


///////////////////////////////////////////////////////////////////////////////
// tab_expand_iterator
//
template< class ForwardIter >
struct tab_expand_iterator;


template< class ForwardIter >
struct tab_expand_iterator_super
{
	typedef boost::iterator_adaptor<
		tab_expand_iterator<ForwardIter>,
		ForwardIter,
		boost::use_default,
		boost::forward_traversal_tag, // sorry
		typename boost::add_const<
			typename boost::iterator_value<ForwardIter>::type
		>::type // not reference but value
	> type;
};


template< class ForwardIter >
struct tab_expand_iterator :
	tab_expand_iterator_super<ForwardIter>::type
{
private:
	typedef typename tab_expand_iterator_super<ForwardIter>::type super_t;
	typedef typename boost::iterator_difference<ForwardIter>::type diff_t;

public:
	// structors
	tab_expand_iterator()
	{ }

	tab_expand_iterator(ForwardIter x, int tabsize) :
		super_t(x), m_tabsize(tabsize),
		m_space_counter(0), m_diff_from_sol(0)
	{ }

private:
	diff_t m_tabsize;
	diff_t m_space_counter;
	diff_t m_diff_from_sol; // from 'start of line'

	// for iterator_adaptor
	friend class boost::iterator_core_access;

	typename super_t::reference dereference() const
	{
		if (!space_is_end() || is_tab())
			return PSTADE_OVEN_TAB_EXPAND_SPACE;

		return *(this->base());
	}

	void increment()
	{
		if (!space_is_end()) {
			space_increment();
			++m_diff_from_sol;
			return;
		}
	
		if (is_tab()) {
			++(this->base_reference()); // see you later

			space_initialize();
			space_increment();
			++m_diff_from_sol;
			return;
		}

		bool nl = is_newline();

		++(this->base_reference());
		++m_diff_from_sol;

		if (nl)
			m_diff_from_sol = 0;
	}

	bool equal(const tab_expand_iterator& other) const
	{
		return
			m_tabsize == other.m_tabsize &&
			this->base() == other.base() &&
			m_space_counter == other.m_space_counter
		;
	}

	// tab specifics
	bool is_tab() const
	{
		return *(this->base()) == PSTADE_OVEN_TAB_EXPAND_TAB;
	}

	bool is_newline() const
	{
		return *(this->base()) == '\n';
	}

	// "pseudo space range" functions
	void space_initialize()
	{
		m_space_counter = m_tabsize - m_diff_from_sol % m_tabsize;
	}

	bool space_is_end() const
	{
		return (m_space_counter == 0);
	}

	void space_increment()
	{
		--m_space_counter;
	}
};


///////////////////////////////////////////////////////////////////////////////
// make_tab_expand_iterator
//
template< class ForwardIter > inline
tab_expand_iterator<ForwardIter>
make_tab_expand_iterator(ForwardIter x, int tabsize)
{
	return tab_expand_iterator<ForwardIter>(x, tabsize);
}


} } // namespace pstade::oven
