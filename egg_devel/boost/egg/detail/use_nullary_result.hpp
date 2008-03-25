#ifndef BOOST_EGG_DETAIL_USE_NULLARY_RESULT_HPP
#define BOOST_EGG_DETAIL_USE_NULLARY_RESULT_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>


namespace boost { namespace egg {


    struct use_nullary_result;


    template< class X, class Then, class Else = X >
    struct if_use_nullary_result :
        mpl::if_< is_same<X, use_nullary_result>,
            Then,
            Else
        >
    { };


    template< class X, class Then, class Else = mpl::identity<X> >
    struct eval_if_use_nullary_result :
        mpl::eval_if< is_same<X, use_nullary_result>,
            Then,
            Else
        >
    { };


} } // namespace boost::egg


#endif
