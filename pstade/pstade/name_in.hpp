#ifndef PSTADE_NAME_IN_HPP
#define PSTADE_NAME_IN_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Pending...: researching now...
//
//


// What:
//
// VC++ default argument name binding is too late,
// then easily falls into the name ambiguity.
// So prefer the qualified name, or
// you can use this macro to say the bug loudly!


#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1400))

    #include <pstade/preprocessor.hpp>

    #define PSTADE_NAME_IN(ScopeSeq) \
        PSTADE_PP_FULLNAME(ScopeSeq)::
    /**/

#else

    #define PSTADE_NAME_IN(ScopeSeq) \
    /**/

#endif


#endif
