#ifndef PSTADE_OVEN_TO_UTF8_HPP
#define PSTADE_OVEN_TO_UTF8_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/regex/pending/unicode_iterator.hpp> // utf8_output_iterator


namespace pstade { namespace oven {


template< class BaseIter > inline
boost::utf8_output_iterator<BaseIter> const
to_utf8(BaseIter const& it)
{
    return boost::utf8_output_iterator<BaseIter>(it);
}


} } // namespace pstade::oven


#endif
