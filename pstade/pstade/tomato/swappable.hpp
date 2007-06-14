#ifndef PSTADE_TOMATO_SWAPPABLE_HPP
#define PSTADE_TOMATO_SWAPPABLE_HPP


// PStade.Tomato
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/apple/atl/base_fwd.hpp> // CAutoPtr
#include <pstade/apple/atl/core_fwd.hpp> // CHeapPtr


namespace ATL {


    template< class E >
    void swap(CAutoPtr<E>& left, CAutoPtr<E>& right)
    {
        CAutoPtr<E> tmp = left;
        left = right;
        right = tmp;
    }


    template< class E, class Allocator >
    void swap(CHeapPtr<E, Allocator>& left, CHeapPtr<E, Allocator>& right)
    {
        CHeapPtr<E, Allocator> tmp = left;
        left = right;
        right = tmp;
    }


} // namespace ATL


#endif
