#pragma once

#include <boost/config.hpp> // for BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
#include <boost/preprocessor/cat.hpp>

// Note:
//   Using-directive is beyond WORKAROUND_ADL.
//   VC6's using-directive is somewhat broken.


#if !defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP)

	#define PSTADE_WORKAROUND_ADL_BARRIER_NAME(id) \
		BOOST_PP_CAT(pstade_adl_barrier_of_, id) \
	/**/

	#define PSTADE_WORKAROUND_ADL_BARRIER_OPEN(id) \
		namespace PSTADE_WORKAROUND_ADL_BARRIER_NAME(id) { } \
		using namespace PSTADE_WORKAROUND_ADL_BARRIER_NAME(id); \
		namespace PSTADE_WORKAROUND_ADL_BARRIER_NAME(id) { \
	/**/

	#define PSTADE_WORKAROUND_ADL_BARRIER_CLOSE(id) \
		} \
	/**/

#else

	#define PSTADE_WORKAROUND_ADL_BARRIER_OPEN(id) \
	/**/

	#define PSTADE_WORKAROUND_ADL_BARRIER_CLOSE(id) \
	/**/

#endif // !defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP)
