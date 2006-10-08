#ifndef PSTADE_CONCEPT_HPP
#define PSTADE_CONCEPT_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Can't wait for the upcoming Boost.Concept...


#if !defined(PSTADE_CONCEPT_NO_CHECK)

    #include <boost/config.hpp>
    #include <boost/detail/workaround.hpp>
    #include <boost/concept/assert.hpp>
    #include <boost/concept/usage.hpp>
    #include <boost/concept/where.hpp>

    #define PSTADE_CONCEPT_ASSERT BOOST_CONCEPT_ASSERT

    #if BOOST_WORKAROUND(__GNUC__, <= 3)
        // GCC seems to require the members be DefaultConstructible
        // without this. 'BOOST_CONCEPT_USAGE' will work around?
        #define PSTADE_CONCEPT_USAGE(Model) Model(); ~Model()
    #else
        #define PSTADE_CONCEPT_USAGE BOOST_CONCEPT_USAGE
    #endif

    #define PSTADE_CONCEPT_WHERE BOOST_CONCEPT_WHERE

#else

    #include <pstade/unparenthesize.hpp>

    #define PSTADE_CONCEPT_ASSERT(ModelInParens)
    #define PSTADE_CONCEPT_USAGE(Model) ~Model()
    // use 'const' outside of this.
    #define PSTADE_CONCEPT_WHERE(Models, Result) PSTADE_UNPARENTHESIZE(Result)

#endif // !defined(PSTADE_CONCEPT_NO_CHECK)


#endif
