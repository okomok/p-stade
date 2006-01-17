#pragma once

// See:
//   http://d.hatena.ne.jp/Cryolite/20050326
//   http://www.kangaroologic.com/interfaces/libs/interfaces/doc/macros/protect.html

#include <boost/type_traits/function_traits.hpp>


#define PSTADE_PROTECT(x) \
	boost::function_traits< void (x) >::arg1_type \
/**/


#define PSTADE_PROTECT_DEPENDENT(x) \
	typename boost::function_traits< void (x) >::arg1_type \
/**/
