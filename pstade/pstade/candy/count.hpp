#ifndef PSTADE_CANDY_COUNT_HPP
#define PSTADE_CANDY_COUNT_HPP


// PStade.Candy
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/int.hpp>
#include <boost/mpl/sizeof.hpp>
#include <boost/mpl/times.hpp>


namespace pstade { namespace candy {


namespace count_detail {


	template< class T >
	struct bitsizeof :
		boost::mpl::times<
			boost::mpl::int_<8>,
			boost::mpl::sizeof_<T>
		>
	{ };


} // namespace count_detail


template< class Flags >
int count(Flags fs)
{
	int count = 0;
	for (int i = 0; i < count_detail::bitsizeof<Flags>::value; ++i) {
		if (fs & 0x01)
			++count;
		fs >>= 1;
	}

	return count;
}


} } // namespace pstade::candy


#endif
