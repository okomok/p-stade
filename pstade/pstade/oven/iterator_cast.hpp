#pragma once

// Note:
//   boost::iterator_cast in Boost.RangeEx also works fine,
//   but it seems not to support eVC4.

#include <boost/config.hpp> // for BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE, BOOST_NO_MEMBER_TEMPLATES
#include <boost/mpl/and.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_scalar.hpp>

namespace pstade { namespace oven {


///////////////////////////////////////////////////////////////////////////////
// PSTADE_OVEN_NO_AUTO_ITERATOR
//
#if defined(BOOST_NO_MEMBER_TEMPLATES)
	#define PSTADE_OVEN_NO_AUTO_ITERATOR
#endif


namespace iterator_cast_detail {

	// Note:
	//   eVC4 doesn't allow functions(in this case, iterator_cast) to be separated
	//   as definition and declaration if it has default arguments.
	template< class BaseIter, class Iterator >
	struct dispatcher;

} // namespace iterator_cast_detail


///////////////////////////////////////////////////////////////////////////////
// iterator_cast
//
template< class BaseIter, class Iterator > inline
BaseIter iterator_cast(Iterator it BOOST_APPEND_EXPLICIT_TEMPLATE_TYPE(BaseIter))
{
	typedef typename iterator_cast_detail::dispatcher<BaseIter, Iterator>::type dispatcher_t;
	return dispatcher_t::call(it);
}


namespace iterator_cast_detail {

	// I don't know what 'is_convertiable' means...
	template< class BaseIter, class Iterator >
	struct is_strictly_convertible :
		boost::mpl::or_<
			boost::is_same<BaseIter, Iterator>,
			boost::mpl::and_<
				boost::is_scalar<BaseIter>,
				boost::is_scalar<Iterator>,
				boost::is_convertible<Iterator, BaseIter>
			>
		>
	{ };

	template< class BaseIter, class Iterator >
	struct as_is
	{
		static BaseIter call(Iterator it)
		{
			return it;
		}
	};

	// Workaround:
	//   The same function names as types often cause name conflicts under eVC4.
	template< class BaseIter, class Iterator >
	struct base_ // base
	{
		static BaseIter call(Iterator it)
		{
			// recursive calls
			return oven::iterator_cast<BaseIter>(it.base());
		}
	};

	template< class BaseIter, class Iterator >
	struct dispatcher :
		boost::mpl::if_<is_strictly_convertible<BaseIter, Iterator>,
			as_is<BaseIter, Iterator>,
			base_<BaseIter, Iterator>
		>
	{ };

} // namespace iterator_cast_detail


#if !defined(PSTADE_OVEN_NO_AUTO_ITERATOR)


namespace iterator_cast_detail {

	template< class Iterator >
	struct auto_iterator_type
	{
		explicit auto_iterator_type(Iterator it) :
			m_it(it)
		{ }

		template< class BaseIter >
		operator BaseIter () const
		{
			return oven::iterator_cast<BaseIter>(m_it);
		}

	private:
		Iterator m_it;
	};

} // namespace iterator_cast_detail


///////////////////////////////////////////////////////////////////////////////
// auto_iterator
//
template< class Iterator > inline
iterator_cast_detail::auto_iterator_type<Iterator> auto_iterator(Iterator it)
{
	return iterator_cast_detail::auto_iterator_type<Iterator>(it);
}


#endif // !defined(PSTADE_OVEN_NO_AUTO_ITERATOR)


} } // namespace pstade::oven
