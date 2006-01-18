#pragma once

#include <boost/config.hpp>
#include "../../config/character_holder_type.hpp"
#include "./bchsetn.hpp"


#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

	#if defined(PSTADE_BISCUIT_CFG_NO_PREPROCESSED_HEADERS)
		#include "../../detail/preprocessing/bchset.hpp"
	#else
		#include "../../detail/preprocessed/bchset.hpp"
	#endif

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
