#ifndef PSTADE_CONCEPT_HPP
#define PSTADE_CONCEPT_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Can't wait for the upcoming Boost.Concept...


#include <boost/version.hpp>


#if !defined(NDEBUG) \
    && BOOST_VERSION >= 103500 \
    && defined(PSTADE_CONCEPT_CHECK)

    #include <boost/config.hpp>
    #include <boost/detail/workaround.hpp>
    #include <boost/concept/assert.hpp>
    #include <boost/concept/usage.hpp>

    #define PSTADE_CONCEPT_ASSERT BOOST_CONCEPT_ASSERT

    #if BOOST_WORKAROUND(__GNUC__, <= 3)
        // GCC seems to require the members be DefaultConstructible
        // without constructor. "./unevaluated.hpp" too can work around.
        #define PSTADE_CONCEPT_USAGE(Model) Model(); BOOST_CONCEPT_USAGE(Model)
    #else
        #define PSTADE_CONCEPT_USAGE BOOST_CONCEPT_USAGE
    #endif

#else

    #include <pstade/unparenthesize.hpp>

    #define PSTADE_CONCEPT_ASSERT(ModelInParens)
    #define PSTADE_CONCEPT_USAGE(Model) ~Model()

#endif // !defined(NDEBUG) && defined(PSTADE_CONCEPT_CHECK)


#endif
