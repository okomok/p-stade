#ifndef PSTADE_EGG_DETAIL_IS_UNARY_BYTAG_OF_HPP
#define PSTADE_EGG_DETAIL_IS_UNARY_BYTAG_OF_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_same.hpp>
#include "./bytag_at.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class By, class Strategy>
    struct is_unary_bytag_of :
        boost::is_same<By, typename bytag_at<Strategy, 1, 0>::type>
    { };


    template<class By1, class By2, class Strategy>
    struct is_unary_bytag_of2 :
        boost::mpl::or_<
            is_unary_bytag_of<By1, Strategy>,
            is_unary_bytag_of<By2, Strategy>
        >
    { };


} } } // namespace pstade::egg::detail


#endif
