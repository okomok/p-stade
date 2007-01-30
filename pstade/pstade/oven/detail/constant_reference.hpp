#ifndef PSTADE_OVEN_DETAIL_CONSTANT_REFERENCE_HPP
#define PSTADE_OVEN_DETAIL_CONSTANT_REFERENCE_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// A helper metafunction to implement constant iterators.


#include <boost/iterator/iterator_traits.hpp>
#include <pstade/affect.hpp>
#include <pstade/remove_cvr.hpp>


namespace pstade { namespace oven { namespace detail {


template< class Iterator >
struct constant_reference
{
    typedef typename
        boost::iterator_reference<Iterator>::type
    ref_t;

    typedef typename
        affect<
            ref_t,
            typename remove_cvr<ref_t>::type const
        >::type
    type;
};


} } } // namespace pstade::oven::detail


#endif
