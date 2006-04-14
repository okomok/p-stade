#ifndef PSTADE_OVEN_JOINT_ITERATOR_HPP
#define PSTADE_OVEN_JOINT_ITERATOR_HPP


// PStade.Oven
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include <boost/iterator/detail/minimum_category.hpp>
#include <boost/iterator/iterator_adaptor.hpp>


namespace pstade { namespace oven {


template< class Iterator1, class Iterator2 >
struct joint_iterator;


namespace joint_iterator_detail {


	template< class Iterator1, class Iterator2 >
	struct traversal
	{
		typedef typename boost::detail::minimum_category<
			boost::forward_traversal_tag,
			typename boost::detail::minimum_category<
				typename boost::iterator_traversal<Iterator1>::type,
				typename boost::iterator_traversal<Iterator2>::type
			>::type
		> type;
	};


	template< class Iterator1, class Iterator2 >
	struct super_
	{
		typedef boost::iterator_adaptor<
			joint_iterator<Iterator1, Iterator2>,
			Iterator1,
			boost::use_default,
			typename traversal<Iterator1, Iterator2>::type
		> type;
	};


} // namespace joint_iterator_detail


template< class Iterator1, class Iterator2  >
struct joint_iterator :
	joint_iterator_detail::super_<Iterator1, Iterator2>::type
{
private:
	typedef joint_iterator self_t;
	typedef typename joint_iterator_detail::super_<Iterator1, Iterator2>::type super_t;
	typedef typename super_t::reference ref_t;
	typedef typename super_t::base_type base_t;

public:
	template< class Iterator1_, class Iterator2_ >
	joint_iterator(Iterator1_ it1, Iterator1_ last1, Iterator2_ it2) :
		super_t(it1), m_last1(last1), m_it2(it2)
	{ }

	template< class Iterator2_ > // normal iterator!
	joint_iterator(Iterator2_ it2) :
		super_t(it2), m_last1(it2), m_it2(it2)
	{ }

	template< class Iterator1_, class Iterator2_ >
	joint_iterator(
		joint_iterator<Iterator1_, Iterator2_> other,
		typename boost::enable_if_convertible<Iterator1, Iterator1_>::type * = 0,
		typename boost::enable_if_convertible<Iterator2, Iterator2_>::type * = 0
	) :
		super_t(other.base()), m_last1(other.first_end()), m_it2(other.second())
	{ }

public:
	Iterator1 first_end() const
	{ return m_last1; }

	Iterator2 second() const
	{ return m_it2; }

private:
	base_t m_last1;
	Iterator2 m_it2;

friend class boost::iterator_core_access;
	ref_t dereference() const
	{
		if (this->base() != m_last1)
			return *this->base();
		else
			return *m_it2;
	}

	bool equal(self_t other) const
	{
		BOOST_ASSERT(m_last1 == other.m_last1 && "incompatible iterators compared");

		return
			this->base() == other.base() &&
			m_it2 == other.m_it2
		;
	}

	void increment()
	{
		if (this->base() != m_last1)
			++this->base_reference();
		else
			++m_it2;
	}
};


template< class Iterator1, class Iterator2 > inline const
joint_iterator<Iterator1, Iterator2>
make_joint_iterator(Iterator1 it1, Iterator1 last1, Iterator2 it2)
{
	return joint_iterator<Iterator1, Iterator2>(it1, last1, it2);
}


} } // namespace pstade::oven


#endif
