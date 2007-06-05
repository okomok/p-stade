#ifndef PSTADE_OVEN_ITERATOR_BASE_HPP
#define PSTADE_OVEN_ITERATOR_BASE_HPP
#include "./prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace oven {


template< class Iterator >
struct iterator_base
{
    typedef typename Iterator::base_type type;
};


} } // namespace pstade::oven


#endif
