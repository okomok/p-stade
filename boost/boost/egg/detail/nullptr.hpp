#ifndef BOOST_EGG_DETAIL_NULLPTR_HPP
#define BOOST_EGG_DETAIL_NULLPTR_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_pointer.hpp>


namespace boost { namespace egg { namespace details {


    // "generic"
    #define BOOST_EGG_NULLPTR 0


    template<class T> inline
    T *nullptr_()
    {
        return 0;
    }


    // better than 'boost::zero<Pointer>::value'?
    template<class Pointer> inline
    Pointer null_()
    {
        BOOST_MPL_ASSERT((is_pointer<Pointer>));
        return 0;
    }


} } } // namespace boost::egg::details


#endif
