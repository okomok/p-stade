#ifndef PSTADE_OVEN_DETAIL_CONSTANT_REFERENCE_HPP
#define PSTADE_OVEN_DETAIL_CONSTANT_REFERENCE_HPP
#include "../prelude.hpp"


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
#include "../read.hpp"


namespace pstade { namespace oven { namespace detail {


template< class ReadableOrLvalueIter >
struct constant_reference :
    affect<
        typename iterator_read<ReadableOrLvalueIter>::type,
        typename boost::iterator_value<ReadableOrLvalueIter>::type const
    >
{ };


} } } // namespace pstade::oven::detail


#endif
