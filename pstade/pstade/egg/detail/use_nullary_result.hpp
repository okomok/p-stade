#ifndef PSTADE_EGG_DETAIL_USE_NULLARY_RESULT_HPP
#define PSTADE_EGG_DETAIL_USE_NULLARY_RESULT_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>


namespace pstade { namespace egg {


    struct use_nullary_result;


    template< class X, class Then, class Else = X >
    struct if_use_nullary_result :
        boost::mpl::if_< boost::is_same<X, use_nullary_result>,
            Then,
            Else
        >
    { };


    template< class X, class Then, class Else = boost::mpl::identity<X> >
    struct eval_if_use_nullary_result :
        boost::mpl::eval_if< boost::is_same<X, use_nullary_result>,
            Then,
            Else
        >
    { };


} } // namespace pstade::egg


#endif
