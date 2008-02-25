#ifndef BOOST_EGG_STATIC_DOWN_HPP
#define BOOST_EGG_STATIC_DOWN_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/ambi.hpp>
#include <boost/egg/by_perfect.hpp>
#include <boost/egg/const.hpp>
#include <boost/egg/implicit.hpp>
#include <boost/egg/static_downcast.hpp>


namespace boost { namespace egg {


    typedef
        result_of_ambi0<
            implicit_ref<X_static_downcast<mpl::_1>, by_perfect>::type,
            by_perfect
        >::type
    T_static_down;

    BOOST_EGG_CONST((T_static_down), static_down)
        = BOOST_EGG_AMBI_L BOOST_EGG_IMPLICIT_REF() BOOST_EGG_AMBI_R;


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
