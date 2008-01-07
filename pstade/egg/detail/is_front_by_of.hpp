#ifndef PSTADE_EGG_DETAIL_IS_FRONT_BY_OF_HPP
#define PSTADE_EGG_DETAIL_IS_FRONT_BY_OF_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/or.hpp>
#include "./by_at.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class By, class Strategy>
    struct is_front_by_of :
        boost::is_same<By, typename by_at<Strategy, 0>::type>
    { };


    template<class By1, class By2, class Strategy>
    struct is_front_by_of2 :
        boost::mpl::or_<
            is_front_by_of<By1, Strategy>,
            is_front_by_of<By2, Strategy>
        >
    { };


} } } // namespace pstade::egg::detail


#endif
