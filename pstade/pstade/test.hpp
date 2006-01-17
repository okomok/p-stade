#pragma once

// Port of: <boost/detail/lightweight_test.hpp>

#include <pstade/print.hpp>

#if !defined(_WIN32_WCE)
	#include <sstream>
	#include <boost/current_function.hpp>
#else
	#include <boost/preprocessor/seq/cat.hpp>
	#include <boost/preprocessor/stringize.hpp>
#endif

namespace pstade {


namespace test_detail {

	inline int& error_count()
	{
		static int x = 0;
		return x;
	}

#if !defined(_WIN32_WCE)
	inline void print_failure(const char *expr, const char *file, int line, const char* function)
	{
		// WinCE has no iostreams.
		std::stringstream msg;
		msg << file << "(" << line << "): test '" << expr << "' failed in function '" << function << "'";
		pstade::print(msg.str());
		++error_count();
	}
#endif

} // namespace test_detail


inline int test_report()
{
	int count = test_detail::error_count();

	if (count == 0) {
		pstade::print("No errors detected.");
		return 0;
	}
	else {
	#if !defined(_WIN32_WCE)
		std::stringstream msg;
		msg << count << " error" << (count == 1 ? "" : "s") << " detected.";
		pstade::print(msg.str());
	#else
		pstade::print("Some errors detected.");
	#endif
		return 1;
	}
}

} // namespace pstade


#if !defined(_WIN32_WCE)

	// Topic: BOOST_PP_CAT makes a problem about __LINE__ with /ZI option.

	#define PSTADE_TEST(expr) \
		((expr) ? (void)0 : \
			pstade::test_detail::print_failure(#expr, __FILE__, __LINE__, BOOST_CURRENT_FUNCTION)) \
	/**/

#else

	#define PSTADE_TEST_DETAIL_INFO(exp) \
		BOOST_PP_STRINGIZE( BOOST_PP_SEQ_CAT( (__FILE__)([)(__LINE__)(])(:)(exp) ) ) \
	/**/

	#define PSTADE_TEST(expr) \
		( (expr) ? (void)0 : \
			(++pstade::test_detail::error_count(), \
			pstade::print(PSTADE_TEST_DETAIL_INFO(expr))) ) \
	/**/

#endif // !defined(_WIN32_WCE)
