#ifndef PSTADE_OVEN_DETAIL_ASSIGN_NEW_HPP
#define PSTADE_OVEN_DETAIL_ASSIGN_NEW_HPP
#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Boost v1.34 'shared_ptr' needs a lvalue 'auto_ptr'.


#include <memory> // auto_ptr


namespace pstade { namespace oven { namespace detail {


    template< class T, class A, class Ptr > inline
    void assign_new(A const& a, Ptr& p)
    {
        std::auto_ptr<T> ap(new T(a));
        p = ap;
    }


} } } // namespace pstade::oven::detail


#endif
