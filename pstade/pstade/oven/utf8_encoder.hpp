#pragma once

#if !defined(PSTADE_CFG_NO_STD_IOSTREAM)


#include <boost/regex/pending/unicode_iterator.hpp> // for utf8_output_iterator

namespace pstade { namespace oven {


template< class BaseIter > inline
boost::utf8_output_iterator<BaseIter>
utf8_encoder(BaseIter it)
{
	return boost::utf8_output_iterator<BaseIter>(it);
}


} } // namespace pstade::oven


#endif // !defined(PSTADE_CFG_NO_STD_IOSTREAM)
