#pragma once

#include <iterator>
#include <boost/range/difference_type.hpp>
#include <boost/range/value_type.hpp>
#include "./push_back.hpp"

namespace pstade { namespace stove {


template< class BackInsertionSeq >
struct back_insert_iterator
{
	typedef std::output_iterator_tag iterator_category;
	typedef typename boost::range_value<BackInsertionSeq>::type value_type;
	typedef typename boost::range_difference<BackInsertionSeq>::type difference_type;
	typedef value_type *pointer;
	typedef value_type& reference;

	explicit back_insert_iterator(BackInsertionSeq& seq) : m_seq(&seq)
	{ }

	back_insert_iterator& operator=(const value_type& val)
	{ 
		stove::push_back(*m_seq, val);
		return *this;
	}
	back_insert_iterator& operator*() { return *this; }
	back_insert_iterator& operator++() { return *this; }
	back_insert_iterator& operator++(int) { return *this; }

private:
	BackInsertionSeq *m_seq; // must be a pointer for assignable
};


template< class BackInsertionSeq > inline
back_insert_iterator<BackInsertionSeq> back_inserter(BackInsertionSeq& seq)
{
	return back_insert_iterator<BackInsertionSeq>(seq);
}


} } // namespace pstade::stove
