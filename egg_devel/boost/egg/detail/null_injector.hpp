#ifndef BOOST_EGG_DTAIL_NULL_INJECTOR_HPP
#define BOOST_EGG_DTAIL_NULL_INJECTOR_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
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


#include <boost/egg/detail/adl_barrier.hpp>


namespace boost { namespace egg { namespace details {


BOOST_EGG_ADL_BARRIER(null_injector) {
    template<class Derived>
    struct null_injector
    { };
}


} } } // namespace boost::egg:details


#endif
