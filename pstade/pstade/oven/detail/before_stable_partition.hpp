#ifndef PSTADE_OVEN_DETAIL_BEFORE_STABLE_PARTITION_HPP
#define PSTADE_OVEN_DETAIL_BEFORE_STABLE_PARTITION_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Works around a bug that SGI STL 'stable_partition'
// requires the 'difference_type' of iterator to be 'ptrdiff_t'.
// See 'stable_partition_adaptive' and 'Temporary_buffer::size()'.


#include "./prelude.hpp"


#include <algorithm>
#if !defined(_ALGORITHM_) // except for VC++ STL

    #include <cstddef> // ptrdiff_t
    #include <pstade/pipable.hpp>
    #include "../identities.hpp"

    namespace pstade { namespace oven {

        PSTADE_PIPABLE(before_stable_partition, (identities_detail::op_make<std::ptrdiff_t>))

    } }

    #define PSTADE_OVEN_BEFORE_STABLE_PARTITION \
        | ::pstade::oven::before_stable_partition \
    /**/

#else

    #define PSTADE_OVEN_BEFORE_STABLE_PARTITION

#endif


#endif
