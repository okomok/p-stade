#ifndef BOOST_EGG_THROW_HPP
#define BOOST_EGG_THROW_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/const.hpp>


namespace boost { namespace egg {


    struct T_throw
    {
        typedef void result_type;

        template<class X>
        void operator()(X const &x) const
        {
            throw x;
        }
    };

    typedef T_throw T_throw_;
    BOOST_EGG_CONST((T_throw_), throw_) = {};


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
