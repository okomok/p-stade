#ifndef PSTADE_USE_NULLARY_RESULT_HPP
#define PSTADE_USE_NULLARY_RESULT_HPP
#include "./prelude.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_same.hpp>


namespace pstade {


    struct use_nullary_result;


    template< class From, class To >
    struct use_nullary_result_to :
        boost::mpl::if_< boost::is_same<From, use_nullary_result>,
            To,
            From
        >
    { };


    template< class From, class ToFun >
    struct use_nullary_result_eval_to :
        boost::mpl::eval_if< boost::is_same<From, use_nullary_result>,
            ToFun,
            boost::mpl::identity<From>
        >
    { };


} // namespace pstade


#endif
