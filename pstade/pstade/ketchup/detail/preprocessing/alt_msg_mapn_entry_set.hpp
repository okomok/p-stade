
#if !defined(BOOST_PP_IS_ITERATING)

	#ifndef KETCHUP_ALT_MSG_MAPN_ENTRY_SET_INCLUDED
		#define KETCHUP_ALT_MSG_MAPN_ENTRY_SET_INCLUDED

		#include <boost/preprocessor/cat.hpp>
		#include <boost/preprocessor/iteration/iterate.hpp>
		#include <boost/preprocessor/iteration/local.hpp>
		#include <boost/preprocessor/repetition/enum_params.hpp>
		#include "../../config/limit_alt_msg_map_size.hpp"
		
		// local macro
		#define PSTADE_KETCHUP_alt_msg_mapn_statement(z, i, unused) \
		if (BOOST_PP_CAT(E, i)::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) \
		{ \
			return true; \
		} \
		/**/

		// header
		namespace pstade { namespace ketchup {

			struct alt_msg_mapn_entry_set
			{

// empty
template<
	DWORD msgMapID
>
struct alt_msg_map0
{
	template< class Derived >
	static bool process(Derived&, HWND, UINT, WPARAM, LPARAM, LRESULT&, DWORD)
	{
		return false;
	}
};


		#define BOOST_PP_ITERATION_LIMITS (1, PSTADE_KETCHUP_LIMIT_ALT_MSG_MAP_SIZE)
		#define BOOST_PP_FILENAME_1 "./alt_msg_mapn_entry_set.hpp"
		#include BOOST_PP_ITERATE()

		// footer
		
			}; // struct alt_msg_mapn_entry_set

		} } // namespace pstade::ketchup
		
		#undef PSTADE_KETCHUP_alt_msg_mapn_statement

	#endif // KETCHUP_ALT_MSG_MAPN_ENTRY_SET_INCLUDED

#else // BOOST_PP_IS_ITERATING

	#define n BOOST_PP_ITERATION()


template<
	DWORD msgMapID,
	BOOST_PP_ENUM_PARAMS(n, class E)
>
struct BOOST_PP_CAT(alt_msg_map, n)
{
	template< class Derived >
	static bool process(Derived& derived, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult, DWORD dwMsgMapID)
	{
		if (msgMapID != dwMsgMapID) { return false; }
		
		#define BOOST_PP_LOCAL_MACRO(n) PSTADE_KETCHUP_alt_msg_mapn_statement(~, n, ~)
		#define BOOST_PP_LOCAL_LIMITS (0, n-1)
		#include BOOST_PP_LOCAL_ITERATE()
		#undef BOOST_PP_LOCAL_MACRO

		return false;
	}
};


	#undef n

#endif // BOOST_PP_IS_ITERATING
