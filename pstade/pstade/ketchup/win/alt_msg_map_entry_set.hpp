#ifndef PSTADE_KETCHUP_WIN_ALT_MSG_MAP_ENTRY_SET_HPP
#define PSTADE_KETCHUP_WIN_ALT_MSG_MAP_ENTRY_SET_HPP


// PStade.Ketchup
//
// Copyright 2005 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/config.hpp> // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#include <boost/microsoft/sdk/windows.hpp>
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


#endif
