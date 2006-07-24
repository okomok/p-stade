#ifndef PSTADE_LIBS_WINE_TEST_STATEMENT_HPP
#define PSTADE_LIBS_WINE_TEST_STATEMENT_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/statement.hpp>


#include <boost/config.hpp>
#include <pstade/instance.hpp>


PSTADE_INSTANCE(int, x, value)


#if defined(BOOST_MSVC)
    PSTADE_STATEMENT(Update,
        x = 3;
        x += 1;
    )
#else
    PSTADE_STATEMENT(Update,
        PSTADE_INSTANCE_OF(x) = 3;
        PSTADE_INSTANCE_OF(x) += 1;
    )
#endif


#endif
