#ifndef PSTADE_OVEN_UTF8_ENCODER_HPP
#define PSTADE_OVEN_UTF8_ENCODER_HPP


// PStade.Oven
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/regex/pending/unicode_iterator.hpp> // utf8_output_iterator


namespace pstade { namespace oven {


template< class BaseIter > inline
boost::utf8_output_iterator<BaseIter>
utf8_encoder(BaseIter it)
{
	return boost::utf8_output_iterator<BaseIter>(it);
}


} } // namespace pstade::oven


#endif
