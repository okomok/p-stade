#pragma once

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#if !BOOST_WORKAROUND(BOOST_MSVC, < 1300)
	#include <boost/mpl/if.hpp>
	#include <boost/mpl/greater.hpp>
	#include <boost/mpl/sizeof.hpp>
#endif

namespace pstade { namespace candy { namespace detail {


template< class Flags0, class Flags1 >
struct greater_size
{
// Workaround: VC6 is crashed by...
#if !BOOST_WORKAROUND(BOOST_MSVC, < 1300)
	typedef typename boost::mpl::if_<
		boost::mpl::greater< boost::mpl::sizeof_<Flags0>, boost::mpl::sizeof_<Flags1> >,
		Flags0,
		Flags1
	>::type type;
#else
	typedef Flags0 type;
#endif

};


} } } // namespace pstade::candy::detail
