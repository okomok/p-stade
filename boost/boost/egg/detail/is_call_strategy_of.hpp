#ifndef BOOST_EGG_DETAIL_IS_CALL_STRATEGY_OF_HPP
#define BOOST_EGG_DETAIL_IS_CALL_STRATEGY_OF_HPP
#include "./prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/and.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/egg/pstade/has_xxx.hpp>


namespace pstade { namespace egg { namespace detail {


    PSTADE_HAS_TYPE(call_strategy)


    template<class Tag, class Little>
    struct is_same_call_strategy :
        boost::is_same<Tag, typename Little::call_strategy>
    { };


    template<class Tag, class Little>
    struct is_call_strategy_of :
        boost::mpl::and_<
            has_call_strategy<Little>,
            is_same_call_strategy<Tag, Little>
        >
    { };


} } } // namespace pstade::egg::detail


#endif
