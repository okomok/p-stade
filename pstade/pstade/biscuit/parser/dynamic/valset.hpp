#pragma once

#include <boost/config.hpp>
#include <boost/mpl/void.hpp>
#include "./valsetn.hpp"

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

	#if defined(PSTADE_BISCUIT_CFG_NO_PREPROCESSED_HEADERS)
		#include "../../detail/preprocessing/valset.hpp"
	#else
		#include "../../detail/preprocessed/valset.hpp"
	#endif

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
