#ifndef BOOST_EGG_DEFERRED_HPP
#define BOOST_EGG_DEFERRED_HPP
#include "./detail/prefix.hpp"


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/placeholders.hpp> // inclusion guaranteed
#include "./detail/as_mpl_lambda.hpp"
#include "./detail/little_deferred.hpp"
#include "./by_perfect.hpp"


namespace pstade { namespace egg {


    template<class Lambda, class Strategy = by_perfect>
    struct deferred
    {
        typedef
            function<detail::little_deferred<Lambda>, Strategy>
        type;
    };


    #define BOOST_EGG_DEFERRED() {{}}


    // If you are a msvc-8.0 user, prefer this macro.
    // Note that BOOST_EGG_AS_MPL_LAMBDA in 'deferred' can't work around.
    #define BOOST_EGG_DEFER(L) \
        pstade::egg::deferred<BOOST_EGG_AS_MPL_LAMBDA(L)>::type \
    /**/

    #define BOOST_EGG_DEFER_BY(L, Bytag) \
        pstade::egg::deferred<BOOST_EGG_AS_MPL_LAMBDA(L), Bytag>::type \
    /**/


} } // namespace pstade::egg


#endif
