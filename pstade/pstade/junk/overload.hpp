#ifndef BOOST_EGG_OVERLOAD_HPP
#define BOOST_EGG_OVERLOAD_HPP
#include <boost/egg/detail/prefix.hpp>


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/iteration/iterate.hpp>
#include <boost/egg/detail/nullary_result_of_overload_set.hpp>
#include <boost/egg/detail/little_overload_result.hpp>
#include <boost/egg/detail/set.hpp> // inclusion guaranteed
#include <boost/egg/variadic.hpp>


namespace boost { namespace egg {


    template<class Sigs, class Strategy = by_perfect>
    struct result_of_overload
        variadic<
            details::little_overload_result<Sigs, Strategy>,
            Strategy,
            use_default,
            typename details::nullary_result_of_overload_set<Sigs>::type
        >
    { };

    #define BOOST_EGG_OVERLOAD_R { {
    #define BOOST_EGG_OVERLOAD_L } }


} } // namespace boost::egg


#include <boost/egg/detail/suffix.hpp>
#endif
