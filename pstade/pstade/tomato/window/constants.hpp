#pragma once

#include <boost/mpl/int.hpp>

namespace pstade { namespace tomato {


struct create_success :
	boost::mpl::int_<0>
{ };

struct create_failure :
	boost::mpl::int_<-1>
{ };


} } // namespace pstade::tomato
