#pragma once

#include <stdexcept> // for range_error
#include <string>
#include <boost/foreach.hpp> // for foreach::tag
#include <boost/iterator/counting_iterator.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/oven/workaround/iterator_range_overload_ambiguity.hpp>
#include <pstade/unused.hpp>

namespace pstade { namespace oven {


namespace counting_range_detail {

	template< class Iterator >
	struct is_bounds_checkable :
		boost::is_same<
			typename boost::iterator_traversal<Iterator>::type,
			boost::random_access_traversal_tag
		>
	{ };

	template< class Incrementable >
	struct no_bounds_check
	{
		static void call(Incrementable n, Incrementable m)
		{
			pstade::unused(n, m);
		}
	};

	template< class Incrementable >
	struct bounds_check
	{
		static void call(Incrementable n, Incrementable m)
		{
			if (n > m) {
				std::string msg("pstade::oven::counting_range - out of bounds");
				boost::throw_exception(std::range_error(msg));
			}
		}
	};

	template< class Incrementable, class Iterator >
	struct bounds_checker :
		boost::mpl::eval_if< is_bounds_checkable<Iterator>,
			boost::mpl::identity< bounds_check<Incrementable> >,
			boost::mpl::identity< no_bounds_check<Incrementable> >
		>::type
	{ };

} // namespace counting_range_detail


///////////////////////////////////////////////////////////////////////////////
// counting_range
//
template<
	class Incrementable,
	class CategoryOrTraversal = boost::use_default,
	class Difference = boost::use_default
>
struct counting_range :
	boost::iterator_range<
		boost::counting_iterator<Incrementable, CategoryOrTraversal, Difference>
	>
{
private:
	typedef boost::counting_iterator<Incrementable, CategoryOrTraversal, Difference> iter_t;
	typedef boost::iterator_range<iter_t> super_t;

public:
	counting_range(Incrementable n, Incrementable m) :
		super_t(iter_t(n), iter_t(m))
	{
		counting_range_detail::bounds_checker<Incrementable, iter_t>::call(n, m);
	}

	PSTADE_OVEN_WORKAROUND_ITERATOR_RANGE_OVERLOAD_AMBIGUITY(counting_range, iter_t)
};


///////////////////////////////////////////////////////////////////////////////
// make_counting_range
//
template< class Incrementable, class CategoryOrTraversal, class Difference > inline
counting_range<Incrementable, CategoryOrTraversal, Difference>
make_counting_range(Incrementable n, Incrementable m, boost::type<CategoryOrTraversal>, boost::type<Difference>)
{
	return counting_range<Incrementable, CategoryOrTraversal, Difference>(n, m);
}

template< class Incrementable, class CategoryOrTraversal > inline
counting_range<Incrementable, CategoryOrTraversal, boost::use_default>
make_counting_range(Incrementable n, Incrementable m, boost::type<CategoryOrTraversal>)
{
	return counting_range<Incrementable, CategoryOrTraversal, boost::use_default>(n, m);
}

template< class Incrementable > inline
counting_range<Incrementable, boost::use_default, boost::use_default>
make_counting_range(Incrementable n, Incrementable m)
{
	return counting_range<Incrementable, boost::use_default, boost::use_default>(n, m);
}


///////////////////////////////////////////////////////////////////////////////
// zero_to
//
template< class ZeroableIncrementable > inline
counting_range<ZeroableIncrementable, boost::use_default, boost::use_default>
zero_to(ZeroableIncrementable c)
{
	return counting_range<ZeroableIncrementable, boost::use_default, boost::use_default>(0, c);
}


///////////////////////////////////////////////////////////////////////////////
// one_to
//
template< class ZeroableIncrementable > inline
counting_range<ZeroableIncrementable, boost::use_default, boost::use_default>
one_to(ZeroableIncrementable c)
{
	return counting_range<ZeroableIncrementable, boost::use_default, boost::use_default>(1, c);
}


} } // namespace pstade::oven


///////////////////////////////////////////////////////////////////////////////
// Boost.Foreach optimization
//
template< class Incrementable, class CategoryOrTraversal, class Difference > inline
boost::mpl::true_
*boost_foreach_is_lightweight_proxy(pstade::oven::counting_range<Incrementable, CategoryOrTraversal, Difference> *&, boost::foreach::tag)
{ return 0; }
