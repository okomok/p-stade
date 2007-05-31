#ifndef PSTADE_VODKA_DRINK_HPP
#define PSTADE_VODKA_DRINK_HPP


// PStade.Vodka
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if defined(_CONSOLE) // How to know the invocation from BJam?

    #include "./drink_msvc.hpp"
    #include <boost/config.hpp> // enable default Boost behavior
    #include "./boost.hpp"

#else

    #include "./boost/detail_lightweight_test.hpp"

#endif


#endif
