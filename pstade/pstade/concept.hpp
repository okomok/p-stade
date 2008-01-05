#ifndef PSTADE_CONCEPT_HPP
#define PSTADE_CONCEPT_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/version.hpp>
#include <pstade/boost_workaround.hpp>


// Note the new concept library is broken on gcc-3.4
// , which wrongly requires DefaultConstructible without BOOST_CONCEPT_USAGE.
#if !defined(NDEBUG) \
    && defined(PSTADE_CONCEPT_CHECK) \
    && !BOOST_WORKAROUND(__GNUC__, <= 3) \
    // && BOOST_VERSION >= 103500

    #define PSTADE_CONCEPT_CHECKING

    #include <boost/concept/assert.hpp>
    #include <boost/concept/usage.hpp>

    #define PSTADE_CONCEPT_ASSERT BOOST_CONCEPT_ASSERT
    #define PSTADE_CONCEPT_USAGE  BOOST_CONCEPT_USAGE

#else

    #define PSTADE_CONCEPT_ASSERT(ModelInParens)
    #define PSTADE_CONCEPT_USAGE(Model) ~Model()

#endif


#endif
