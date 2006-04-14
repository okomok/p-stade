#ifndef PSTADE_OVEN_COUNTING_RANGE_HPP
#define PSTADE_OVEN_COUNTING_RANGE_HPP


// PStade.Oven
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <stdexcept> // range_error
#include <string>
#include <boost/iterator/counting_iterator.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type.hpp>
#include <boost/type_traits/is_same.hpp>
#include <pstade/unused.hpp>
#include "./is_lightweight_proxy.hpp"


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
	explicit counting_range(Incrementable n, Incrementable m) :
		super_t(iter_t(n), iter_t(m))
	{
		counting_range_detail::bounds_checker<Incrementable, iter_t>::call(n, m);
	}
};


template< class Incrementable, class CategoryOrTraversal, class Difference > inline const
counting_range<Incrementable, CategoryOrTraversal, Difference>
make_counting_range(Incrementable n, Incrementable m, boost::type<CategoryOrTraversal>, boost::type<Difference>)
{
	return counting_range<Incrementable, CategoryOrTraversal, Difference>(n, m);
}

template< class Incrementable, class CategoryOrTraversal > inline const
counting_range<Incrementable, CategoryOrTraversal, boost::use_default>
make_counting_range(Incrementable n, Incrementable m, boost::type<CategoryOrTraversal>)
{
	return counting_range<Incrementable, CategoryOrTraversal, boost::use_default>(n, m);
}

template< class Incrementable > inline const
counting_range<Incrementable, boost::use_default, boost::use_default>
make_counting_range(Incrementable n, Incrementable m)
{
	return counting_range<Incrementable, boost::use_default, boost::use_default>(n, m);
}


template< class ZeroableIncrementable > inline const
counting_range<ZeroableIncrementable, boost::use_default, boost::use_default>
zero_to(ZeroableIncrementable c)
{
	return counting_range<ZeroableIncrementable, boost::use_default, boost::use_default>(0, c);
}


template< class ZeroableIncrementable > inline const
counting_range<ZeroableIncrementable, boost::use_default, boost::use_default>
one_to(ZeroableIncrementable c)
{
	return counting_range<ZeroableIncrementable, boost::use_default, boost::use_default>(1, c);
}


} } // namespace pstade::oven


PSTADE_OVEN_IS_LIGHTWEIGHT_PROXY_TEMPLATE(pstade::oven::counting_range, 3)


#endif
