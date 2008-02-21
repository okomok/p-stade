#ifndef BOOST_EGG_DETAIL_SAFE_BOOL_HPP
#define BOOST_EGG_DETAIL_SAFE_BOOL_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://www.artima.com/cppsource/safebool.html
// http://www.pdc.kth.se/training/Talks/C++/boost/libs/utility/operators.htm#safe_bool_note
// http://lists.boost.org/Archives/boost/2003/11/56857.php
// <boost/spirit/core/safe_bool.hpp>


#include <boost/egg/const.hpp>
#include <boost/egg/detail/nullptr.hpp>


namespace boost { namespace egg { namespace details {


    struct safe_bool_box
    {
        int true_;
    };

    typedef int safe_bool_box::*safe_bool;


    struct T_make_safe_bool
    {
        typedef safe_bool result_type;

        // delay evaluation using template to suppress VC++ warning.
        template<class Expr>
        result_type operator()(Expr const &b) const
        {
            return b ? &safe_bool_box::true_ : BOOST_EGG_NULLPTR;
        }
    };

    BOOST_EGG_CONST((T_make_safe_bool), make_safe_bool) = {};


    BOOST_EGG_CONST((safe_bool), safe_true)  = &safe_bool_box::true_;
    BOOST_EGG_CONST((safe_bool), safe_false) = BOOST_EGG_NULLPTR;


} } } // namespace boost::egg::details


#endif
