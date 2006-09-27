#ifndef PSTADE_OVEN_DETAIL_CONCEPT_CHECK_HPP
#define PSTADE_OVEN_DETAIL_CONCEPT_CHECK_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Waiting for new Boost.Concept library with Boost 1.34...


// Question:
//
// Functors are often no default-constructible,
// but Forward Tarversal Iterator must be default-constructible.
// Thus, filter_iterator etc cannot conform to it.


#include <boost/concept_check.hpp>
#include <boost/range/concepts.hpp>
#include <boost/type_traits/remove_cv.hpp>


#if defined(PSTADE_OVEN_CFG_ENABLE_CONCEPT_CHECK)

    #define PSTADE_OVEN_DETAIL_REQUIRES(Range, Concept) \
        typedef void (boost::Concept< typename boost::remove_cv<Range>::type >::* func##Range##Concept)(); \
        template< func##Range##Concept Tp1_ > \
        struct concept_checking_##Range##Concept { }; \
        typedef concept_checking_##Range##Concept< \
            BOOST_FPTR boost::Concept< typename boost::remove_cv<Range>::type >::constraints \
        > concept_checking_typedef_##Range##Concept \
    /**/

#else

    #define PSTADE_OVEN_DETAIL_REQUIRES(Range, Concept) \
    /**/

#endif


namespace pstade { namespace oven { namespace detail {


template< class Concept > inline
void requires()
{
#if defined(PSTADE_OVEN_CFG_ENABLE_CONCEPT_CHECK)

#if !defined(NDEBUG)
    typedef typename boost::remove_cv<Concept>::type con_t;
    boost::function_requires<con_t>();
#endif

#endif
}


} } } // namespace pstade::oven::detail


#endif
