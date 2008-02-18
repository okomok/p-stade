#ifndef BOOST_EGG_DELETE_HPP
#define BOOST_EGG_DELETE_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/checked_delete.hpp>
#include <boost/egg/const.hpp>


namespace boost { namespace egg {


    struct T_delete
    {
        typedef void result_type;

        template<class X>
        void operator()(X *p) const
        {
            boost::checked_delete(p);
        }
    };

    typedef T_delete T_delete_;
    BOOST_EGG_CONST((T_delete_), delete_) = {};


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
