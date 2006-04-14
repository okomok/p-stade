#ifndef PSTADE_GARLIC_PUSH_BACK_HPP
#define PSTADE_GARLIC_PUSH_BACK_HPP


// PStade.Garlic
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/if.hpp>
#include <pstade/apple/basic_ostream_fwd.hpp>
#include <pstade/apple/is_sequence.hpp>
#include <pstade/overload.hpp>


namespace pstade { namespace garlic {


namespace push_back_detail {


	struct std_sequence
	{
		template< class Sequence, class ValueT >
		static void call(Sequence& seq, const ValueT& val)
		{
			seq.push_back(val);
			// seq.insert(seq.end(), val);
		}
	};


	struct adl_customization
	{
		template< class T, class ValueT >
		static void call(T& x, const ValueT& val)
		{
			pstade_garlic_push_back(x, val, overload());
		}
	};


} // namespace push_back_detail


template< class BackInsertable, class ValueT > inline
void push_back(BackInsertable& bi, const ValueT& val)
{
	typedef typename
	boost::mpl::if_<apple::is_sequence<BackInsertable>,
		push_back_detail::std_sequence,
		push_back_detail::adl_customization
	>::type impl_t;

	impl_t::call(bi, val);
}


} } // namespace pstade::garlic


// customizations
//

template< class CharT, class Traits, class ValueT > inline
void pstade_garlic_push_back(
	std::basic_ostream<CharT, Traits>& os,
	const ValueT& val, pstade::overload)
{
	os << val;
}


#endif
