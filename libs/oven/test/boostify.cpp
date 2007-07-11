#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if 1
    namespace pstade {
        namespace oven { }
    }

    namespace boost {
        namespace oven = pstade::oven;
    }
#endif


#include <pstade/oven/oven.hpp>


int main()
{
    boost::oven::always("hello, boost");
    return 0;
}
