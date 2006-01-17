
#if !defined(BOOST_PP_IS_ITERATING)

		#include <boost/preprocessor/cat.hpp>
		#include <boost/preprocessor/iteration/iterate.hpp>
		#include <boost/preprocessor/repetition/enum_params.hpp>
		#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
		#include "../../config/limit_alt_msg_map_size.hpp"

		// local macro
		#define PSTADE_KETCHUP_alt_msg_map_statement(z, i, unused) \
		if (BOOST_PP_CAT(E, i)::process(derived, hWnd, uMsg, wParam, lParam, lResult, dwMsgMapID)) \
		{ \
			return true; \
		} \
		/**/

		// header
		namespace pstade { namespace ketchup {

			struct alt_msg_map_entry_set : alt_msg_mapn_entry_set
			{

// primary
template<
	DWORD msgMapID,
	BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(PSTADE_KETCHUP_LIMIT_ALT_MSG_MAP_SIZE, class E, boost::mpl::void_)
>
struct alt_msg_map :
	BOOST_PP_CAT(alt_msg_map, PSTADE_KETCHUP_LIMIT_ALT_MSG_MAP_SIZE)<
		msgMapID,
		BOOST_PP_ENUM_PARAMS(PSTADE_KETCHUP_LIMIT_ALT_MSG_MAP_SIZE, E)
	>
{
};

// empty
template<
	DWORD msgMapID
>
struct alt_msg_map<
	msgMapID
> :
	alt_msg_map0<msgMapID>
{
};


		#define BOOST_PP_ITERATION_LIMITS (1, PSTADE_KETCHUP_LIMIT_ALT_MSG_MAP_SIZE-1)
		#define BOOST_PP_FILENAME_1 "./alt_msg_map_entry_set.hpp"
		#include BOOST_PP_ITERATE()

		// footer
		
			}; // struct alt_msg_map_entry_set

		} } // namespace pstade::ketchup

		#undef PSTADE_KETCHUP_alt_msg_map_statement

#else // BOOST_PP_IS_ITERATING

	#define n BOOST_PP_ITERATION()


template<
	DWORD msgMapID,
	BOOST_PP_ENUM_PARAMS(n, class E)
>
struct alt_msg_map<
	msgMapID,
	BOOST_PP_ENUM_PARAMS(n, E)
> :
	BOOST_PP_CAT(alt_msg_map, n)<
		msgMapID,
		BOOST_PP_ENUM_PARAMS(n, E)
	>
{
};


	#undef n

#endif // BOOST_PP_IS_ITERATING
