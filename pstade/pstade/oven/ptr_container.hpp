#ifndef PSTADE_OVEN_PTR_CONTAINER_HPP
#define PSTADE_OVEN_PTR_CONTAINER_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/prelude.hpp"
#include <boost/type_traits/remove_const.hpp>
#include "./do_iter_swap.hpp"


namespace boost {


    template< class VoidIter, class T >
    class void_ptr_iterator;


    template< class VoidIter, class T > inline
    void iter_swap(void_ptr_iterator<VoidIter, T> left, void_ptr_iterator<VoidIter, T> right)
    {
        pstade::oven::do_iter_swap(left.base(), right.base());
    }


    template< class Iterator >
    struct iterator_value;


    // This seems a bug of Boost.PtrContainer.
    template< class VoidIter, class T >
    struct iterator_value< void_ptr_iterator<VoidIter, T> > :
        remove_const<T>
    { };


} // namespace boost


#endif
