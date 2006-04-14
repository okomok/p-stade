#ifndef PSTADE_DIET_RESET_OSTREAM_HPP
#define PSTADE_DIET_RESET_OSTREAM_HPP


// PStade.Diet
//
// Copyright 2006 MB.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/os.hpp"


namespace pstade { namespace diet {


template< class StringOutputable > inline
void reset_ostream(StringOutputable& out)
{
	detail::os.reset(out);
}


} } // namespace pstade::diet


#endif
