
#if !defined(BOOST_PP_IS_ITERATING)

		#include <boost/preprocessor/cat.hpp>
		#include <boost/preprocessor/comparison/equal.hpp>
		#include <boost/preprocessor/iteration/iterate.hpp>
		#include <boost/preprocessor/iteration/local.hpp>
		#include <boost/preprocessor/repetition/enum_params.hpp>
		#include "../../config/limit_begin_msg_map_size.hpp"

		// local macro
		#define PSTADE_KETCHUP_begin_msg_mapn_statement(z, i, unused) \
		if (BOOST_PP_CAT(E, i)::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) \
		{ \
			return true; \
		} \
		/**/

		// header

		namespace pstade { namespace ketchup {

			struct begin_msg_mapn_entry_set
			{

// empty
template< class Dummy = boost::mpl::void_  >
struct begin_msg_map0
{
	template< class Derived >
	static bool process(Derived&, HWND, UINT, WPARAM, LPARAM, LRESULT&, DWORD)
	{
		return false;
	}
};


		#define BOOST_PP_ITERATION_LIMITS (1, PSTADE_KETCHUP_LIMIT_BEGIN_MSG_MAP_SIZE)
		#define BOOST_PP_FILENAME_1 "./begin_msg_mapn_entry_set.hpp"
		#include BOOST_PP_ITERATE()

		// clean up
		
			}; // struct begin_msg_mapn_entry_set

		} } // namespace pstade::ketchup
		
		#undef PSTADE_KETCHUP_begin_msg_mapn_statement

#else // BOOST_PP_IS_ITERATING

	#define n BOOST_PP_ITERATION()


template<
	BOOST_PP_ENUM_PARAMS(n, class E)
>
struct BOOST_PP_CAT(begin_msg_map, n)
{
	template< class Derived >
	static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
	{
		#define BOOST_PP_LOCAL_MACRO(n) PSTADE_KETCHUP_begin_msg_mapn_statement(~, n, ~)
		#define BOOST_PP_LOCAL_LIMITS (0, n-1)
		#include BOOST_PP_LOCAL_ITERATE()
		#undef BOOST_PP_LOCAL_MACRO

		return false;
	}
};


	#undef n

#endif // BOOST_PP_IS_ITERATING
