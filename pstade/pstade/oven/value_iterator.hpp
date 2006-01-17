#pragma once

#include <cstddef> // for ptrdiff_t
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/ref.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <pstade/assert.hpp>

namespace pstade { namespace oven {


///////////////////////////////////////////////////////////////////////////////
// value_iterator
//
template< class ValueT, class DifferenceT >
struct value_iterator;


namespace value_iterator_detail {

	template< class ValueT >
	struct unwrap_ref
	{
		typedef typename boost::mpl::eval_if<
			boost::is_reference_wrapper<ValueT>,
			boost::add_reference< typename boost::unwrap_reference<ValueT>::type >,
			boost::mpl::identity<ValueT>
		>::type val_t;

		typedef typename boost::add_const<val_t>::type type;
	};

	template< class ValueT, class DifferenceT >
	struct super_
	{
		typedef boost::iterator_adaptor<
			value_iterator<ValueT, DifferenceT>, // Derived
			DifferenceT, // Base!!
			ValueT, // Value
			boost::random_access_traversal_tag, // Traversal
			typename unwrap_ref<ValueT>::type, // Reference
			DifferenceT // Difference
		> type;
	};

} // namespace value_iterator_detail


template< class ValueT, class DifferenceT = std::ptrdiff_t >
struct value_iterator :
	value_iterator_detail::super_<ValueT, DifferenceT>::type
{
private:
	typedef typename value_iterator_detail::super_<ValueT, DifferenceT>::type super_t;

public:
	value_iterator(ValueT val, DifferenceT sz) :
		m_value(val), m_size(sz)
	{ }

	typename super_t::reference dereference() const
	{
		PSTADE_ASSERT(m_size != 0);
		return m_value;
	}

	void advance(DifferenceT d)
	{
		m_size -= d;
		PSTADE_ASSERT(m_size >= 0);
	}

	void increment()
	{
		m_size -= 1;
		PSTADE_ASSERT(m_size >= 0);
	}

	bool equal(const value_iterator& other) const
	{
		return
			m_value == other.m_value &&
			m_size == other.m_size
		;
	}

private:
	ValueT m_value;
	DifferenceT m_size;
};


///////////////////////////////////////////////////////////////////////////////
// make_value_iterator
//
template< class ValueT, class DifferenceT > inline
value_iterator<ValueT, DifferenceT>
make_value_iterator(ValueT val, DifferenceT sz)
{
	return value_iterator<ValueT, DifferenceT>(val, sz);
}


} } // namespace pstade::oven
