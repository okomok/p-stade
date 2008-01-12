#ifndef PSTADE_RADISH_NULL_INJECTOR_HPP
#define PSTADE_RADISH_NULL_INJECTOR_HPP


// PStade.Radish
//
// Copyright Shunsuke Sogame 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


/*=============================================================================
    Copyright (c) 2003 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/


// What:
//
// msvc-7.1 may complain if the bases contain the same type.
// Hence, make an empty base type as unique as possible.


#include <boost/egg/pstade/adl_barrier.hpp>


namespace pstade { namespace radish {

PSTADE_ADL_BARRIER(null_injector) {


template< class Derived >
struct null_injector
{ };


} // ADL barrier

} } // namespace pstade::radish


#endif
