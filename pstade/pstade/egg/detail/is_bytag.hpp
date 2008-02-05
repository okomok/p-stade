#ifndef PSTADE_EGG_DETAIL_IS_BYTAG_HPP
#define PSTADE_EGG_DETAIL_IS_BYTAG_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include "../function_fwd.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class X>
    struct is_bytag_impl :
        boost::mpl::or_<
            boost::is_same<X, by_perfect>,
            boost::is_same<X, by_ref>,
            boost::is_same<X, by_cref>,
            boost::is_same<X, by_value>
        >
    { };


    template<class X>
    struct is_bytag :
        is_bytag_impl<typename boost::remove_cv<X>::type>
    { };


} } } // namespace pstade::egg::detail


#endif
