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


// Note:
//
// A 'const' must be outside of 'PSTADE_CONCEPT_WHERE'.
//
// PSTADE_CONCEPT_WHERE(...
// ((void)) const make_const_value();


#if !defined(NDEBUG) && !defined(PSTADE_CONCEPT_OFF)

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

    #include <boost/preprocessor/seq/seq.hpp> // SEQ_HEAD

    #define PSTADE_CONCEPT_ASSERT(ModelInParens)
    #define PSTADE_CONCEPT_USAGE(Model) ~Model()
    #define PSTADE_CONCEPT_WHERE(Models, Result) \
        typename pstade::concept_detail::unparen<void BOOST_PP_SEQ_HEAD(Models), void Result>::type

#endif // !defined(PSTADE_CONCEPT_OFF)


#include <pstade/void.hpp>


namespace pstade { namespace concept_detail {

    // 'typename' needs a dependent-name.
    // Unlike 'PSTADE_UNPARENTHESIZE',
    // we have 'Models' as the dependent-name.

    template< class ModelFn, class Result >
    struct unparen;

    template< class ModelFn, class Result >
    struct unparen< ModelFn, void(Result) >
    {
        typedef Result type;
    };

    template< class ModelFn >
    struct unparen< ModelFn, void(void_) >
    {
        typedef void type;
    };

} } // namespace pstade::concept_detail


#endif
