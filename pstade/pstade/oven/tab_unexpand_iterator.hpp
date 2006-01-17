#pragma once

#include <algorithm>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_traits.hpp> // for iterator_value
#include <boost/type_traits/add_const.hpp>
#include <pstade/assert.hpp>
#include "./tab_expand_iterator.hpp"

#if !defined(PSTADE_OVEN_TAB_UNEXPAND_DEBUG_MODE)
	#define PSTADE_OVEN_TAB_UNEXPAND_SPACE ' '
	#define PSTADE_OVEN_TAB_UNEXPAND_TAB '\t'
#else
	#define PSTADE_OVEN_TAB_UNEXPAND_SPACE 'S'
	#define PSTADE_OVEN_TAB_UNEXPAND_TAB 'T'
#endif

namespace pstade { namespace oven {


///////////////////////////////////////////////////////////////////////////////
// tab_unexpand_iterator
//
template< class ForwardIter >
struct tab_unexpand_iterator;


template< class ForwardIter >
struct tab_unexpand_iterator_super
{
	typedef boost::iterator_adaptor<
		tab_unexpand_iterator<ForwardIter>,
		tab_expand_iterator<ForwardIter> // look! :-)
	> type;
};


template< class ForwardIter >
struct tab_unexpand_iterator :
	tab_unexpand_iterator_super<ForwardIter>::type
{
private:
	typedef typename tab_unexpand_iterator_super<ForwardIter>::type super_t;
	typedef typename super_t::base_type base_t;
	typedef typename super_t::difference_type diff_t;

public:
	// structors
	tab_unexpand_iterator()
	{ }

	tab_unexpand_iterator(ForwardIter x, ForwardIter last, int tabsize) :
		super_t(base_t(x, tabsize)), m_last(last, tabsize), m_sol(x, tabsize), m_tabsize(tabsize)
	{ }

private:
	base_t m_last;
	base_t m_sol; // start of line
	diff_t m_tabsize;

	// for iterator_adaptor
	friend class boost::iterator_core_access;

	typename super_t::reference dereference() const
	{
		if (flying_distance() != 0)
			return PSTADE_OVEN_TAB_UNEXPAND_TAB;

		return *(this->base());
	}

	void increment()
	{
		diff_t d = flying_distance();
		if (d != 0) {
			std::advance(this->base_reference(), d);
			return;
		}

		bool nl = is_newline();

		++(this->base_reference());

		if (nl)
			m_sol = this->base();
	}

	bool equal(const tab_unexpand_iterator& other) const
	{
		return
			m_tabsize == other.m_tabsize &&
			this->base() == other.base()
		;
	}

	// tab specifics
	bool is_newline() const
	{
		return *(this->base()) == '\n';
	}

	diff_t flying_distance() const
	{
		diff_t diff_from_sol = std::distance(m_sol, this->base());
		diff_t diff_required = m_tabsize - diff_from_sol % m_tabsize;
		
		if (diff_required == 1)
			return false; // common sense?
		
		if (diff_required <= space_exploration())
			return diff_required;
		else
			return 0;
	}

	diff_t space_exploration() const
	{
		diff_t spaces = 0;
		for (base_t it = this->base(); it != m_last; ++it) {
			if (*it == PSTADE_OVEN_TAB_UNEXPAND_SPACE)
				++spaces;
			else
				break;

			if (spaces == m_tabsize) // Apolo 13
				break;
		}

		return spaces;
	}
};


///////////////////////////////////////////////////////////////////////////////
// make_tab_unexpand_iterator
//
template< class ForwardIter > inline
tab_unexpand_iterator<ForwardIter>
make_tab_unexpand_iterator(ForwardIter x, ForwardIter last, int tabsize)
{
	return tab_unexpand_iterator<ForwardIter>(x, last, tabsize);
}


} } // namespace pstade::oven
