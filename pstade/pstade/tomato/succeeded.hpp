#ifndef PSTADE_TOMATO_SUCCEEDED_HPP
#define PSTADE_TOMATO_SUCCEEDED_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/sdk/winerror.hpp>


namespace pstade { namespace tomato {


template< class StatusT > inline
bool succeeded(StatusT s)
{
    // Todo:
    // S_FALSE warning should be added here?

    return SUCCEEDED(s);
}


} } // namespace pstade::tomato


#endif
