#ifndef PSTADE_CANDY_SET_HPP
#define PSTADE_CANDY_SET_HPP


// PStade.Candy
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/assert.hpp>
#include "./add.hpp"
#include "./count.hpp"


namespace pstade { namespace candy {


template< class Flags, class Flag > inline
Flags& set(Flags& fs, Flag f)
{
    BOOST_ASSERT("multiple flags not allowed" && candy::count(f) == 1);
    return candy::add(fs, f);
}


} } // namespace pstade::candy


#endif
