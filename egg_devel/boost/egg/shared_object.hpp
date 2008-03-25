#ifndef BOOST_EGG_SHARED_OBJECT_HPP
#define BOOST_EGG_SHARED_OBJECT_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/pointee.hpp>
#include <boost/egg/by_perfect.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/implicit.hpp>
#include <boost/egg/shared_new.hpp>


namespace boost { namespace egg {


    typedef 
        implicit<
            X_shared_new<pointee<mpl::_1>, mpl::_2>,
            by_perfect
        >::type
    T_shared_object;

    BOOST_EGG_CONST((T_shared_object), shared_object) = BOOST_EGG_IMPLICIT();


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
