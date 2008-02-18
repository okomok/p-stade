#ifndef BOOST_EGG_POLY_HPP
#define BOOST_EGG_POLY_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/placeholders.hpp> // inclusion guaranteed
#include <boost/egg/detail/before_mpl_apply.hpp>
#include <boost/egg/detail/little_poly.hpp>
#include <boost/egg/by_perfect.hpp>


namespace boost { namespace egg {


    template<class Expr, class Strategy = by_perfect, class NullaryResult = use_default>
    struct poly
    {
        typedef
            function<details::little_poly<BOOST_EGG_BEFORE_MPL_APPLY_TPL(Expr), NullaryResult>, Strategy>
        type;
    };

    #define BOOST_EGG_POLY() {{}}


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
