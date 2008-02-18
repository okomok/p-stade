#ifndef BOOST_EGG_IS_SAME_OBJ_HPP
#define BOOST_EGG_IS_SAME_OBJ_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/addressof.hpp>
#include <boost/egg/const.hpp>


namespace boost { namespace egg {


    struct T_is_same_obj
    {
        typedef bool result_type;

        template<class X, class Y>
        bool operator()(X const &x, Y const &y) const
        {
            return boost::addressof(x) == boost::addressof(y);
        }
    };

    BOOST_EGG_CONST((T_is_same_obj), is_same_obj) = {};


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
