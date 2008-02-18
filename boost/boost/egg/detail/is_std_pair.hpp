#ifndef BOOST_EGG_DETAIL_IS_STD_PAIR_HPP
#define BOOST_EGG_DETAIL_IS_STD_PAIR_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/bool.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/egg/detail/std_pair_fwd.hpp>


namespace boost { namespace egg { namespace details {


    template<class X>
    struct is_std_pair_aux :
        mpl::false_
    { };

    template<class T, class U>
    struct is_std_pair_aux< std::pair<T, U> > :
        mpl::true_
    { };


    template<class X>
    struct is_std_pair :
        is_std_pair_aux<typename remove_cv<X>::type>
    { };


} } } // namespace boost::egg::details


#endif
