#ifndef PSTADE_SAUSAGE_ENUMERATE_HPP
#define PSTADE_SAUSAGE_ENUMERATE_HPP


// PStade.Sausage
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Concepts:
//
// Enumerable: properly customized using below
// EnumFunctor: 'if (fun(x))' is valid


#include "./customization.hpp"
#include "./detail/customization_of_type.hpp"


namespace pstade { namespace sausage {


namespace enumerate_detail {


	template< class Enumerable, class EnumFtor > inline
	EnumFtor aux(Enumerable& e, EnumFtor fun)
	{
		typedef typename detail::customization_of<Enumerable>::type cust_t;
		typedef typename cust_t::template enumerate_argument<Enumerable>::type arg_t;

		return cust_t().template enumerate<arg_t>(e, fun);
	};


} // namespace enumerate_detail


template< class Enumerable, class EnumFtor > inline
EnumFtor enumerate(Enumerable& e, EnumFtor fun)
{
	return enumerate_detail::aux(e, fun);
};


template< class Enumerable, class EnumFtor > inline
EnumFtor enumerate(const Enumerable& e, EnumFtor fun)
{
	return enumerate_detail::aux(e, fun);
};


} } // namespace pstade::sausage


#endif
