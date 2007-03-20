#ifndef PSTADE_OVEN_TRAVERSAL_TAGS_HPP
#define PSTADE_OVEN_TRAVERSAL_TAGS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/iterator/iterator_categories.hpp>
#include <pstade/constant.hpp>
#include "./range_traversal.hpp"


namespace pstade { namespace oven {


PSTADE_CONSTANT(in_single_pass,   (boost::single_pass_traversal_tag))
PSTADE_CONSTANT(in_forward,       (boost::forward_traversal_tag))
PSTADE_CONSTANT(in_bidirectional, (boost::bidirectional_traversal_tag))
PSTADE_CONSTANT(in_random_access, (boost::random_access_traversal_tag))


// A range may be too long to diagnose.
// You should guarantee RandomAccess before applying 'distance'.

struct op_is_random_access
{
    typedef bool result_type;

    bool aux(boost::random_access_traversal_tag) const
    {
        return true;
    }

    bool aux(boost::single_pass_traversal_tag) const
    {
        return false;
    }

    template< class Range >
    bool operator()(Range const&) const
    {
        return aux(typename range_traversal<Range>::type());
    }
};

PSTADE_CONSTANT(is_random_access, (op_is_random_access))


} } // namespace pstade::oven


#endif
