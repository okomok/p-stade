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


namespace pstade { namespace oven {


struct recursive_tag
{ };

template< class Traversal >
struct recursive :
    Traversal,
    recursive_tag
{
    typedef Traversal type;

    recursive()
    { }

    // Workaround:
    // VC7.1 'is_convertible' needs 'const&'.
    recursive(Traversal const&)
    { }
};


PSTADE_CONSTANT(in_single_pass,   (boost::single_pass_traversal_tag))
PSTADE_CONSTANT(in_forward,       (boost::forward_traversal_tag))
PSTADE_CONSTANT(in_bidirectional, (boost::bidirectional_traversal_tag))
PSTADE_CONSTANT(in_random_access, (boost::random_access_traversal_tag))


} } // namespace pstade::oven


#endif
