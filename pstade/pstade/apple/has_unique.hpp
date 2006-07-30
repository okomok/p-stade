#ifndef PSTADE_APPLE_HAS_UNIQUE_HPP
#define PSTADE_APPLE_HAS_UNIQUE_HPP


// PStade.Apple
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Port of: Boost.RangeEx
//
// Copyright 2004 Eric Niebler.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/remove_cvr.hpp>
#include "./is_list.hpp"


namespace pstade { namespace apple {


template< class T, class = void >
struct has_unique_impl :
    is_list<T>
{ };


template< class T >
struct has_unique :
    has_unique_impl<
        typename remove_cvr<T>::type
    >
{ };


} } // namespace pstade::apple


#endif
