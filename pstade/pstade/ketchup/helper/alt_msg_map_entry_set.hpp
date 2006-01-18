#pragma once

#include <boost/config.hpp> // for BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include "./alt_msg_mapn_entry_set.hpp"
	
#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

	#include <boost/mpl/void.hpp>

	#if !defined(PSTADE_KETCHUP_CFG_NO_PREPROCESSED_HEADERS)
		#include "../detail/preprocessed/alt_msg_map_entry_set.hpp"
	#else
		#include "../detail/preprocessing/alt_msg_map_entry_set.hpp"
	#endif

#else

	namespace pstade { namespace ketchup {

		struct alt_msg_map_entry_set : alt_msg_mapn_entry_set
		{ };

	} } // namespace pstade::ketchup

#endif // !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
