#ifndef BOOST_EGG_DETAIL_STD_FORWARD_HPP
#define BOOST_EGG_DETAIL_STD_FORWARD_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/identity.hpp>


namespace boost { namespace egg {


    template<class T> inline
    T &&std_forward(typename mpl::identity<T>::type &&a)
    {
        return a;
    }


} } // namespace boost::egg


#endif
