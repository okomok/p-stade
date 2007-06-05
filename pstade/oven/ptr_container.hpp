#ifndef PSTADE_OVEN_PTR_CONTAINER_HPP
#define PSTADE_OVEN_PTR_CONTAINER_HPP
#include "./prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/type_traits/remove_cv.hpp>
#include "./do_iter_swap.hpp"


namespace boost {


    template< class VoidIter, class T >
    class void_ptr_iterator;


    template< class VoidIter1, class T1, class VoidIter2, class T2 > inline
    void iter_swap(void_ptr_iterator<VoidIter1, T1> it1, void_ptr_iterator<VoidIter2, T2> it2, int = 0)
    {
        pstade::oven::do_iter_swap(it1.base(), it2.base());
    }


    template< class Iterator >
    struct iterator_value;

    // Work around non-conforming 'value_type' bug.
    template< class VoidIter, class T >
    struct iterator_value< void_ptr_iterator<VoidIter, T> > :
        remove_cv<T>
    { };


} // namespace boost


#endif
