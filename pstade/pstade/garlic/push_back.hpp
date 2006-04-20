#ifndef PSTADE_GARLIC_PUSH_BACK_HPP
#define PSTADE_GARLIC_PUSH_BACK_HPP


// PStade.Garlic
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/if.hpp>
#include <boost/utility/enable_if.hpp>
#include <pstade/apple/basic_ostream_fwd.hpp>
#include <pstade/apple/is_sequence.hpp>
#include <pstade/has_xxx.hpp>
#include <pstade/overload.hpp>
#include "./access.hpp"


namespace pstade { namespace garlic {


namespace push_back_detail {


	PSTADE_HAS_TYPE(pstade_garlic_back_insertable)


	struct member_function
	{
		template< class T, class ValueT > static
		void call(T& x, const ValueT& val)
		{
			access::detail_push_back(x, val);
		}
	};


	template< class T, class ValueT > inline
	void pstade_garlic_push_back(T& x, const ValueT& val)
	{
		pstade_garlic_push_back(x, val, overload());
	}

	struct adl_customization
	{
		template< class T, class ValueT > static
		void call(T& x, const ValueT& val)
		{
			pstade_garlic_push_back(x, val);
		}
	};


} // namespace push_back_detail


template< class BackInsertable, class ValueT > inline
void push_back(BackInsertable& bi, const ValueT& val)
{
	typedef typename
	boost::mpl::if_<
		push_back_detail::has_pstade_garlic_back_insertable<BackInsertable>,
		push_back_detail::member_function,
		push_back_detail::adl_customization
	>::type impl_t;

	impl_t::call(bi, val);
}


} } // namespace pstade::garlic


// predefined customizations
//

template< class Sequence, class ValueT > inline
typename boost::enable_if<pstade::apple::is_sequence<Sequence>, void>::type
pstade_garlic_push_back(Sequence& seq, const ValueT& val, pstade::overload)
{
	seq.push_back(val);
}


template< class CharT, class Traits, class ValueT > inline
void pstade_garlic_push_back(std::basic_ostream<CharT, Traits>& os, const ValueT& val, pstade::overload)
{
	os << val;
}


#endif
