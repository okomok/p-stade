#ifndef PSTADE_DETAIL_CLONABLE_HPP
#define PSTADE_DETAIL_CLONABLE_HPP
#include "./prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/ptr_container/clone_allocator.hpp>


namespace pstade { namespace detail_ {


    template<class X> inline
    X *clonable_new(X const& x)
    {
        return boost::heap_clone_allocator::allocate_clone(x);
    }

    template<class X> inline
    void clonable_delete(X *ptr)
    {
        return boost::heap_clone_allocator::deallocate_clone(ptr);
    }


} } // namespace pstade::detail_


#endif
