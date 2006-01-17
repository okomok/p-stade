#pragma once 

#include <boost/config.hpp>
#include "./shortestn.hpp"


#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

	#if defined(PSTADE_BISCUIT_CFG_NO_PREPROCESSED_HEADERS)
		#include "../../detail/preprocessing/shortest.hpp"
	#else
		#include "../../detail/preprocessed/shortest.hpp"
	#endif

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
