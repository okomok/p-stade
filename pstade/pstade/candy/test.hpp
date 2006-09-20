#ifndef PSTADE_CANDY_TEST_HPP
#define PSTADE_CANDY_TEST_HPP


// PStade.Candy
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note. Some win32 flags can be 0; it's dangerous.


#include <boost/assert.hpp>
#include "./count.hpp"
#include "./test_any.hpp"


namespace pstade { namespace candy {


template< class Flags, class Flag > inline
bool test(Flags const& fs, Flag const& f)
{
    BOOST_ASSERT("multiple flags not allowed" && candy::count(f) == 1);
    return candy::test_any(fs, f);
}


} } // namespace pstade::candy


#endif
