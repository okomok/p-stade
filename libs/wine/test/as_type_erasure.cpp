#include <pstade/vodka/drink.hpp>


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/as_type_erasure.hpp>


int main()
{
    pstade::T_as_type_erasure x = pstade::as_type_erasure;
    (void)x;

    return 0;
}
