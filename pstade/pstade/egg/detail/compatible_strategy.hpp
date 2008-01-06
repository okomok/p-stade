#ifndef PSTADE_EGG_DETAIL_COMPATIBLE_STRATEGY_HPP
#define PSTADE_EGG_DETAIL_COMPATIBLE_STRATEGY_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_same.hpp>
#include "../function_fwd.hpp"


namespace pstade { namespace egg { namespace detail {


    template<class Strategy>
    struct compatible_strategy :
        Strategy
    { };

    template< >
    struct compatible_strategy<by_perfect>
    {
        typedef by_perfect type;
    };

    template< >
    struct compatible_strategy<by_ref>
    {
        typedef by_ref type;
    };

    template< >
    struct compatible_strategy<by_cref>
    {
        typedef by_cref type;
    };

    template< >
    struct compatible_strategy<by_value>
    {
        typedef by_value type;
    };


    template<class Strategy, class Strategy_>
    struct is_compatible_strategy :
        boost::is_same<
            typename compatible_strategy<Strategy>::type,
            typename compatible_strategy<Strategy_>::type
        >
    { };


    template<class Strategy, class Strategy1, class Strategy2>
    struct is_compatible_strategy2 :
        boost::mpl::or_<
            is_compatible_strategy<Strategy, Strategy1>,
            is_compatible_strategy<Strategy, Strategy2>
        >
    { };


} } } // namespace pstade::egg::detail


#endif
