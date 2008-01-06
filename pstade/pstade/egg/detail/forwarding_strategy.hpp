#ifndef PSTADE_EGG_DETAIL_FORWARDING_STRATEGY_HPP
#define PSTADE_EGG_DETAIL_FORWARDING_STRATEGY_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <pstade/has_xxx.hpp>
#include <pstade/use_default.hpp>
#include "../by_perfect.hpp"


namespace pstade { namespace egg { namespace detail {


    PSTADE_HAS_TYPE(forwarding_strategy)


    template<class Little>
    struct get_forwarding_strategy
    {
        typedef typename Little::forwarding_strategy type;
    };


    template<class Little, class Strategy>
    struct forwarding_strategy :
        eval_if_use_default<Strategy,
            boost::mpl::eval_if< has_forwarding_strategy<Little>,
                get_forwarding_strategy<Little>,
                boost::mpl::identity<by_perfect>
            >
        >
    { };


} } } // namespace pstade::egg::detail


#endif
