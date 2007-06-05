#ifndef PSTADE_NULLPTR_HPP
#define PSTADE_NULLPTR_HPP
#include "./prelude.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_pointer.hpp>


namespace pstade {


    // "generic"
    #define PSTADE_NULLPTR 0


    template<class T> inline
    T *nullptr_()
    {
        return 0;
    }


    // better than 'boost::zero<Pointer>::value'?
    template<class Pointer> inline
    Pointer null_()
    {
        BOOST_MPL_ASSERT((boost::is_pointer<Pointer>));
        return 0;
    }


} // namespace pstade


#endif
