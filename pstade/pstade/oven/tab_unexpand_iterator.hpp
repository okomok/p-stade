#ifndef PSTADE_OVEN_TAB_UNEXPAND_ITERATOR_HPP
#define PSTADE_OVEN_TAB_UNEXPAND_ITERATOR_HPP


// PStade.Oven
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> // advance, distance
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/iterator_traits.hpp> // iterator_value
#include <boost/type_traits/add_const.hpp>
#include "./detail/config.hpp" // DEBUG_SPACE_CH
#include "./tab_expand_iterator.hpp"


namespace pstade { namespace oven {


template< class ForwardIter >
struct tab_unexpand_iterator;


namespace tab_unexpand_iterator_detail {


	template< class ForwardIter >
	struct super_
	{
		typedef boost::iterator_adaptor<
			tab_unexpand_iterator<ForwardIter>,
			tab_expand_iterator<ForwardIter> // look! :-)
		> type;
	};


} // namespace tab_unexpand_iterator_detail


template< class ForwardIter >
struct tab_unexpand_iterator :
	tab_unexpand_iterator_detail::super_<ForwardIter>::type
{
private:
	typedef typename tab_unexpand_iterator_detail::super_<ForwardIter>::type super_t;
	typedef typename super_t::base_type base_t;
	typedef typename super_t::difference_type diff_t;
	typedef typename super_t::pointer ptr_t;
	typedef typename super_t::value_type val_t;

public:
	explicit tab_unexpand_iterator()
	{ }

	explicit tab_unexpand_iterator(
		ForwardIter it, ForwardIter last,
		int tabsize, val_t& space_ch, val_t& tab_ch
	) :
		super_t(base_t(it, tabsize, space_ch)),
		m_last(last, tabsize, space_ch),
		m_sol(it, tabsize, space_ch), m_tabsize(tabsize),
		m_tab_pch(&tab_ch)
	{ }

private:
	base_t m_last;
	base_t m_sol;		// start of line
	diff_t m_tabsize;
	ptr_t m_tab_pch;	// needs tab character resource for mutability

	bool is_newline() const
	{
		// TODO: make more strict...
		//
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
			if (*it == PSTADE_OVEN_DEBUG_SPACE_CH)
				++spaces;
			else
				break;

			if (spaces == m_tabsize) // Apolo 13
				break;
		}

		return spaces;
	}

friend class boost::iterator_core_access;

	typename super_t::reference dereference() const
	{
		if (flying_distance() != 0)
			return *m_tab_pch;

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
};


template< class ForwardIter > inline const
tab_unexpand_iterator<ForwardIter>
make_tab_unexpand_iterator(
	ForwardIter it, ForwardIter last, int tabsize,
	typename boost::iterator_value<ForwardIter>::type& space_ch,
	typename boost::iterator_value<ForwardIter>::type& tab_ch
)
{
	return tab_unexpand_iterator<ForwardIter>(it, last, tabsize, space_ch, tab_ch);
}


} } // namespace pstade::oven


#endif
