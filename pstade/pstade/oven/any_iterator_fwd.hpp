#ifndef PSTADE_OVEN_ANY_ITERATOR_FWD_HPP
#define PSTADE_OVEN_ANY_ITERATOR_FWD_HPP
#include "./prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Edd points the forward declaration is useful.
// http://www.mr-edd.co.uk/?p=36


#include "./detail/use_default_fwd.hpp"


namespace pstade { namespace oven {


template<
    class Reference,
    class Traversal,
    class Value      = boost::use_default,
    class Difference = boost::use_default
>
struct any_iterator;


} } // namespace pstade::oven


#endif
