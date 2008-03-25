#ifndef BOOST_EGG_FUSE_HPP
#define BOOST_EGG_FUSE_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/by_perfect.hpp>
#include <boost/egg/by_value.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/construct_braced2.hpp>
#include <boost/egg/detail/little_fuse_result.hpp>
#include <boost/egg/generator.hpp>


namespace boost { namespace egg {


    template<class Base>
    struct result_of_fuse
    {
        typedef
            function<details::little_fuse_result<Base>, by_perfect>
        type;
    };

    #define BOOST_EGG_FUSE_L { {
    #define BOOST_EGG_FUSE_R } }
    #define BOOST_EGG_FUSE(F) BOOST_EGG_FUSE_L F BOOST_EGG_FUSE_R


    typedef
        generator<
            result_of_fuse< deduce<mpl::_1, as_value> >::type,
            by_value,
            X_construct_braced2<>
        >::type
    T_fuse;

    BOOST_EGG_CONST((T_fuse), fuse) = BOOST_EGG_GENERATOR();


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
