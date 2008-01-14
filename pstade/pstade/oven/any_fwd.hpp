#ifndef PSTADE_OVEN_ANY_FWD_HPP
#define PSTADE_OVEN_ANY_FWD_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Edd Dawson pointed out that forward declaration is useful.
// http://www.mr-edd.co.uk/?page_id=43


#include <pstade/apple/boost/use_default_fwd.hpp>


namespace pstade { namespace oven {


// iterators
//

template<
    class Reference,
    class Traversal,
    class Value      = boost::use_default,
    class Difference = boost::use_default
>
struct any_iterator;

template< class Reference >
struct any_output_iterator;

template<
    class Reference,
    class Value      = boost::use_default,
    class Difference = boost::use_default
>
struct any_indexed_iterator;


// ranges
//

template<
    class Reference,
    class Traversal,
    class Value      = boost::use_default,
    class Difference = boost::use_default
>
struct any_range;

template<
    class Reference,
    class Value      = boost::use_default,
    class Difference = boost::use_default
>
struct any_indexed;


} } // namespace pstade::oven


#endif
