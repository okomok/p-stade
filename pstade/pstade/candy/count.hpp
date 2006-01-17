#pragma once

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
