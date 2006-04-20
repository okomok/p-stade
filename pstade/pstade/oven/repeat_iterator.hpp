#ifndef PSTADE_OVEN_REPEAT_ITERATOR_HPP
#define PSTADE_OVEN_REPEAT_ITERATOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// This iterator cannot conform to even ForwardIterator for now.
//
// http://article.gmane.org/gmane.comp.lib.boost.devel/140639


#include <iterator>
#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>


namespace pstade { namespace oven {


template< class Iterator, class CountT >
struct repeat_iterator;


namespace repeat_iterator_detail {


	template< class Iterator, class CountT >
	struct super_
	{
		typedef boost::iterator_adaptor<
			repeat_iterator<Iterator, CountT>,
			Iterator,
			boost::use_default,
			std::input_iterator_tag
		> type;
	};


} // namespace repeat_iterator_detail


template< class Iterator, class CountT >
struct repeat_iterator :
	repeat_iterator_detail::super_<Iterator, CountT>::type
{
private:
	typedef repeat_iterator self_t;
	typedef typename repeat_iterator_detail::super_<Iterator, CountT>::type super_t;
	typedef typename super_t::difference_type diff_t;
	typedef typename super_t::reference ref_t;

public:
	template< class OtherIter, class OtherCountT >
	explicit repeat_iterator(OtherIter first, OtherIter last, OtherCountT count) :
		super_t(first), m_first(first), m_last(last), m_count(count)
	{ }

	const Iterator source_begin() const
	{ return m_first; }

	const Iterator source_end() const
	{ return m_last; }

private:
	Iterator m_first, m_last;
	CountT m_count;

friend class boost::iterator_core_access;
	ref_t dereference() const
	{
		BOOST_ASSERT(m_count != 0);

		return *this->base();
	}

	void increment()
	{
		BOOST_ASSERT(m_count != 0);

		increment_impl();
	}

	bool equal(const self_t& other) const
	{
		return
			this->base() == other.base() &&
			m_count == other.m_count
		;
	}

private:
	void increment_impl()
	{
		++this->base_reference();
		if (this->base() == m_last) {
			this->base_reference() = m_first;
			--m_count;
		}
	}
};


template< class Iterator, class CountT > inline const
repeat_iterator<Iterator, CountT>
make_repeat_iterator(Iterator first, Iterator last, CountT count)
{
	return repeat_iterator<Iterator, CountT>(first, last, count);
}


} } // namespace pstade::oven


#endif
