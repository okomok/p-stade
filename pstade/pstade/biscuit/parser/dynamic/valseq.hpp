#pragma once

#include <boost/config.hpp>
#include <boost/mpl/void.hpp>
#include "valseqn.hpp"


#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

	#if defined(PSTADE_BISCUIT_CFG_NO_PREPROCESSED_HEADERS)
		#include "../../detail/preprocessing/valseq.hpp"
	#else
		#include "../../detail/preprocessed/valseq.hpp"
	#endif

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION
