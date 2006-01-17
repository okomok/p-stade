#pragma once

// Note:
//   GCC3.4.4 cannot order overloadings of non-const-reference and const-reference
//   if it has explicit template arguments.
//   So disable the non-const-reference overloading in the case of const-reference.
//
// See:
//   http://groups.google.com/group/comp.lang.c++.moderated/browse_frm/thread/2dc6189c2eec0fd5/

#include <boost/config.hpp> // for BOOST_NO_SFINAE
#include <boost/detail/workaround.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/utility/enable_if.hpp> // for boost::disable_if

namespace pstade {


#if !defined(BOOST_NO_SFINAE)

	template< class T, class R >
	struct disable_if_const :
		boost::disable_if< boost::is_const<T>, R >
	{ };

	template< class T, class R >
	struct lazy_disable_if_const :
		boost::lazy_disable_if< boost::is_const<T>, R >
	{ };

#else

	// God bless you.

	template< class T, class R >
	struct disable_if_const :
		boost::mpl::identity<R>
	{
	#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
		typedef typename boost::mpl::identity<R>::type type;
	#endif
	};

	template< class T, class R >
	struct lazy_disable_if_const :
		R
	{
	#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
		typedef typename R::type type;
	#endif
	};

#endif // !defined(BOOST_NO_SFINAE)


} // namespace pstade
