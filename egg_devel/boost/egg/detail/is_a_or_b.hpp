#ifndef BOOST_EGG_DETAIL_IS_A_OR_B_HPP
#define BOOST_EGG_DETAIL_IS_A_OR_B_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_same.hpp>


namespace boost { namespace egg { namespace details {


    template<class T, class U1, class U2>
    struct is_a_or_b :
        mpl::or_<
            is_same<T, U1>,
            is_same<T, U2>
        >
    { };


} } } // namespace boost::egg::details


#endif
