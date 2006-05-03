#ifndef PSTADE_OVEN_REPEAT_ITERATOR_HPP
#define PSTADE_OVEN_REPEAT_ITERATOR_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <iterator> // distance
#include <boost/assert.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/reverse_iterator.hpp>


namespace pstade { namespace oven {


template< class Iterator, class SizeT >
struct repeat_iterator;


namespace repeat_iterator_detail {


	template< class Iterator, class SizeT >
	struct super_
	{
		typedef boost::iterator_adaptor<
			repeat_iterator<Iterator, SizeT>,
			Iterator
		> type;
	};


	template< class SizeT >
	struct reverse_size
	{
		explicit reverse_size(SizeT index) :
			m_index(index)
		{ }

		SizeT operator++()
		{ return --m_index; }

		template< class SizeT_ >
		void operator+=(SizeT_ index)
		{ m_index -= index; }

		SizeT base() const
		{ return m_index; }

	private:
		SizeT m_index;
	};


	template< class Iterator, class SizeT >
	void increment(Iterator& it, SizeT& index, Iterator first, Iterator last)
	{
		BOOST_ASSERT(std::distance(first, last) >= 0);

		if (++it == last) {
			it = first;
			++index;
		}
	}


	template< class Iterator, class SizeT >
	void decrement(Iterator& it, SizeT& index, Iterator first, Iterator last)
	{
		BOOST_ASSERT(std::distance(first, last) >= 0);

		if (it != first) {
			--it;
		}
		else {
            it = --last;
			--index;
        }
	}


	template< class Difference, class Iterator, class SizeT >
	Difference pseudo_diff(Iterator it, SizeT index, Iterator first, Iterator last)
	{
		Difference srcSize = last - first;
		Difference srcDiff = it - first;
		return (srcSize * index) + srcDiff;
	}


	template< class Iterator, class SizeT, class Difference >
	void advance(Iterator& it, SizeT& index, Difference diff, Iterator first, Iterator last)
	{
		BOOST_ASSERT(diff >= 0);
		BOOST_ASSERT(std::distance(first, last) >= 0);

		Difference srcSize = last - first;
		Difference srcDiff = it - first;
		Difference indexDiff = srcDiff + diff;
		it = first + (indexDiff % srcSize);
		index += (indexDiff / srcSize);
	}


} // namespace repeat_iterator_detail


template< class Iterator, class SizeT >
struct repeat_iterator :
	repeat_iterator_detail::super_<Iterator, SizeT>::type
{
private:
	typedef typename repeat_iterator_detail::super_<Iterator, SizeT>::type super_t;
	typedef typename super_t::difference_type diff_t;
	typedef typename super_t::reference ref_t;

public:
	explicit repeat_iterator()
	{ }

	explicit repeat_iterator(Iterator it, SizeT index, Iterator first, Iterator last) :
		super_t(it), m_index(index),
		m_first(first), m_last(last)		
	{ }

	template< class Iterator_, class Countable_ >
	repeat_iterator(
		repeat_iterator<Iterator_, Countable_> other,
		typename boost::enable_if_convertible<Iterator_, Iterator>::type * = 0,
		typename boost::enable_if_convertible<Countable_, SizeT>::type * = 0
	) :
		super_t(other.base()), m_index(other.index()),
		m_first(other.sbegin()), m_last(other.send())		
	{ }

	const Iterator sbegin() const
	{ return m_first; }

	const Iterator send() const
	{ return m_last; }

	const SizeT index() const
	{ return m_index; }

private:
	Iterator m_first, m_last;
	SizeT m_index;

friend class boost::iterator_core_access;
	ref_t dereference() const
	{
		BOOST_ASSERT(m_index >= 0);

		return *this->base();
	}

	void increment()
	{
		BOOST_ASSERT(m_index >= 0);

		repeat_iterator_detail::increment(this->base_reference(), m_index, m_first, m_last);

		BOOST_ASSERT(m_index >= 0);
	}

	void decrement()
	{
		BOOST_ASSERT(m_index >= 0);

		repeat_iterator_detail::decrement(this->base_reference(), m_index, m_first, m_last);

		BOOST_ASSERT(m_index >= 0);
	}

	void advance(diff_t d)
	{
		BOOST_ASSERT(m_index >= 0);

		if (d >= 0) {
			repeat_iterator_detail::advance(this->base_reference(), m_index, d, m_first, m_last);
		}
		else {
			boost::reverse_iterator<Iterator> rit(this->base());
			boost::reverse_iterator<Iterator> rfirst(m_last), rlast(m_first);
			repeat_iterator_detail::reverse_size<SizeT> rindex(m_index);
			repeat_iterator_detail::advance(rit, rindex, -d, rfirst, rlast);

			this->base_reference() = rit.base();
			m_index = rindex.base();
		}

		BOOST_ASSERT(m_index >= 0);
	}

	diff_t distance_to(repeat_iterator other) const
	{
		return 
			repeat_iterator_detail::pseudo_diff<diff_t>(other.base(), other.index(), other.sbegin(), other.send())
				- repeat_iterator_detail::pseudo_diff<diff_t>(this->base(), m_index, m_first, m_last)
		;
	}

	bool equal(repeat_iterator other) const
	{
		BOOST_ASSERT(m_index >= 0);
		BOOST_ASSERT(
			m_first == other.sbegin() &&
			m_last == other.send() &&
			"incompatible iterators"
		);

		return
			this->base() == other.base() &&
			m_index == other.m_index
		;
	}
};


template< class Iterator, class SizeT > inline const
repeat_iterator<Iterator, SizeT>
make_repeat_iterator(Iterator it, SizeT index, Iterator first, Iterator last)
{
	return repeat_iterator<Iterator, SizeT>(it, index, first, last);
}


} } // namespace pstade::oven


#endif
