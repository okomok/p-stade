#ifndef PSTADE_CONCEPT_HPP
#define PSTADE_CONCEPT_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Copyright Eric Niebler 2006. Distributed under the Boost 
// Software License, Version 1.0. (See accompanying 
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) 


// What:
//
// Can't wait for the upcoming Boost.Concept...


// Note:
//
// A 'const' must be outside of 'PSTADE_CONCEPT_WHERE'.
//
// PSTADE_CONCEPT_WHERE(...
// (int)) const make_const_value();


#if !defined(NDEBUG) && defined(PSTADE_CONCEPT_CHECK)

    #include <boost/config.hpp>
    #include <boost/detail/workaround.hpp>
    #include <boost/concept/assert.hpp>
    #include <boost/concept/usage.hpp>
    #include <boost/concept/where.hpp>

    #define PSTADE_CONCEPT_ASSERT BOOST_CONCEPT_ASSERT

    #if BOOST_WORKAROUND(__GNUC__, <= 3)
        // GCC seems to require the members be DefaultConstructible
        // without constructor. 'BOOST_CONCEPT_USAGE' will work around?
        #define PSTADE_CONCEPT_USAGE(Model) Model(); BOOST_CONCEPT_USAGE(Model)
    #else
        #define PSTADE_CONCEPT_USAGE BOOST_CONCEPT_USAGE
    #endif

    #define PSTADE_CONCEPT_WHERE BOOST_CONCEPT_WHERE

#else

    #include <pstade/unparenthesize.hpp>

    #define PSTADE_CONCEPT_ASSERT(ModelInParens)
    #define PSTADE_CONCEPT_USAGE(Model) ~Model()

    // 'typename' is legal here even if 'Result' is not dependent,
    // because this macro appears in a template. (C++98 14.6/5)
    #define PSTADE_CONCEPT_WHERE(Models, Result) \
        PSTADE_UNPARENTHESIZE_TPL(Result) \
    /**/

#endif // !defined(NDEBUG) && defined(PSTADE_CONCEPT_CHECK)


#include <boost/assert.hpp>

namespace pstade {

    // If you dislike to declare members...,
    // (also, this can work around GCC bug mentioned above.)
    template<class X> inline
    X& unknown_lvalue()
    { 
        BOOST_ASSERT(false); 
        throw "never link 'pstade::unknown_lvalue'!";
    }

} // namespace pstade


#endif
