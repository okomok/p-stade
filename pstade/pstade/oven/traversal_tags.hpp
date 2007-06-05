#ifndef PSTADE_OVEN_TRAVERSAL_TAGS_HPP
#define PSTADE_OVEN_TRAVERSAL_TAGS_HPP
#include "./prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_categories.hpp>
#include <boost/preprocessor/cat.hpp>
#include <pstade/constant.hpp>
#include "./range_traversal.hpp"


namespace pstade { namespace oven {


PSTADE_CONSTANT(in_single_pass,   (boost::single_pass_traversal_tag))
PSTADE_CONSTANT(in_forward,       (boost::forward_traversal_tag))
PSTADE_CONSTANT(in_bidirectional, (boost::bidirectional_traversal_tag))
PSTADE_CONSTANT(in_random_access, (boost::random_access_traversal_tag))


// We sometimes need runtime-check around TraversalCategory.
// For example, a range may be too long to diagnose, then
// you have to guarantee RandomAccess before applying 'distance'.

#define PSTADE_is_(Trv) \
    struct BOOST_PP_CAT(op_is_, Trv) \
    { \
        typedef bool result_type; \
        \
        bool aux(boost::BOOST_PP_CAT(Trv, _traversal_tag)) const \
        { \
            return true; \
        } \
        \
        bool aux(boost::incrementable_traversal_tag) const \
        { \
            return false; \
        } \
        \
        template< class Range > \
        bool operator()(Range const&) const \
        { \
            return aux(typename range_traversal<Range>::type()); \
        } \
    }; \
    \
    PSTADE_CONSTANT(BOOST_PP_CAT(is_, Trv), (BOOST_PP_CAT(op_is_, Trv))) \
/**/

    PSTADE_is_(single_pass)
    PSTADE_is_(forward)
    PSTADE_is_(bidirectional)
    PSTADE_is_(random_access)

#undef  PSTADE_is_


} } // namespace pstade::oven


#endif
