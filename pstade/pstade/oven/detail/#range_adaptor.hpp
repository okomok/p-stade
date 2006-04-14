#ifndef PSTADE_OVEN_RANGE_ADAPTOR_HPP
#define PSTADE_OVEN_RANGE_ADAPTOR_HPP


// PStade.Oven
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/add_const.hpp>
#include <boost/utility/result_of.hpp>
#include <pstade/instance.hpp>
#include <pstade/unused.hpp>


namespace pstade { namespace oven {


namespace range_adaptor_detail {


	// 0ary
	template< class Function >
	struct adaptor0
	{ };


	template< class Range, class Function > inline
	typename boost::result_of<Function(Range&)>::type
	operator|(Range& rng, const adaptor0<Function>& ad)
	{
		pstade::unused(ad);
		return Function()(rng);
	}

	template< class Range, class Function > inline
	typename boost::result_of<Function(const Range&)>::type
	operator|(const Range& rng, const adaptor0<Function>& ad)
	{
		pstade::unused(ad);
		return Function()(rng);
	}


	// 1ary
	template< class Function, class A0 >
	struct adaptor1
	{
		explicit adaptor1(A0& a0) :
			m_a0(a0)
		{ }

		mutable A0& m_a0;
	};


	template< class Range, class Function, class A0 > inline
	typename boost::result_of<Function(Range&, A0&)>::type
	operator|(Range& rng, const adaptor1<Function, A0>& ad)
	{
		return Function()(rng, ad.m_a0);
	}

	template< class Range, class Function, class A0 > inline
	typename boost::result_of<Function(const Range&, A0&)>::type
	operator|(const Range& rng, const adaptor1<Function, A0>& ad)
	{
		return Function()(rng, ad.m_a0);
	}


	// 2ary
	template< class Function, class A0, class A1 >
	struct adaptor2
	{
		explicit adaptor2(A0& a0, A1& a1) :
			m_a0(a0), m_a1(a1)
		{ }

		mutable A0& m_a0;
		mutable A1& m_a1;
	};


	template< class Range, class Function, class A0, class A1 > inline
	typename boost::result_of<Function(Range&, A0&, A1&)>::type
	operator|(Range& rng, const adaptor2<Function, A0, A1>& ad)
	{
		return Function()(rng, ad.m_a0, ad.m_a1);
	}

	template< class Range, class Function, class A0, class A1 > inline
	typename boost::result_of<Function(const Range&, A0&, A1&)>::type
	operator|(const Range& rng, const adaptor2<Function, A0, A1>& ad)
	{
		return Function()(rng, ad.m_a0, ad.m_a1);
	}


} // namespace range_adaptor_detail


template< class Function >
struct range_adaptor
{
	// 0ary
	range_adaptor_detail::adaptor0<Function>
	operator()() const
	{
		return range_adaptor_detail::adaptor0<Function>();
	}


	// 1ary
	template< class A0 >
	range_adaptor_detail::adaptor1<Function, A0>
	operator()(A0& a0) const
	{
		return range_adaptor_detail::adaptor1<Function, A0>(a0);
	}

	template< class A0 >
	range_adaptor_detail::adaptor1<Function, typename boost::add_const<A0>::type>
	operator()(const A0& a0) const
	{
		return range_adaptor_detail::adaptor1<Function, typename boost::add_const<A0>::type>(a0);
	}

	// 2ary
	template< class A0, class A1 >
	range_adaptor_detail::adaptor2<Function, A0, A1>
	operator()(A0& a0, A0& a1) const
	{
		return range_adaptor_detail::adaptor2<Function, A0, A1>(a0, a1);
	}

	template< class A0, class A1 >
	range_adaptor_detail::adaptor2<Function, typename boost::add_const<A0>::type, A1>
	operator()(const A0& a0, A0& a1) const
	{
		return range_adaptor_detail::adaptor2<Function, typename boost::add_const<A0>::type, A1>(a0, a1);
	}

	template< class A0, class A1 >
	range_adaptor_detail::adaptor2<Function, A0, typename boost::add_const<A1>::type>
	operator()(A0& a0, const A0& a1) const
	{
		return range_adaptor_detail::adaptor2<Function, A0, typename boost::add_const<A1>::type>(a0, a1);
	}

	template< class A0, class A1 >
	range_adaptor_detail::adaptor2<Function, typename boost::add_const<A0>::type, typename boost::add_const<A1>::type>
	operator()(const A0& a0, const A0& a1) const
	{
		return range_adaptor_detail::adaptor2<Function, typename boost::add_const<A0>::type, typename boost::add_const<A1>::type>(a0, a1);
	}
};


// passed as is
//
template< class Range, class Function > inline
typename boost::result_of<Function(Range&)>::type
operator|(Range& rng, const range_adaptor<Function>& ad)
{
	pstade::unused(ad);
	return Function()(rng);
}

template< class Range, class Function > inline
typename boost::result_of<Function(const Range&)>::type
operator|(const Range& rng, const range_adaptor<Function>& ad)
{
	pstade::unused(ad);
	return Function()(rng);
}


} } // namespace pstade::oven


#define PSTADE_OVEN_RANGE_ADAPTOR(Name, Fun) \
	PSTADE_INSTANCE_CONST(pstade::oven::range_adaptor< Fun >, Name) \
/**/


#endif
