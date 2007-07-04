#ifndef PSTADE_EGG_ADAPT_HPP
#define PSTADE_EGG_ADAPT_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy tuple_at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/placeholders.hpp> // inclusion guaranteed
#include "./detail/as_mpl_lambda.hpp"
#include "./detail/baby_adapt.hpp"
#include "./function.hpp"


namespace pstade { namespace egg {


    template<class Lambda>
    struct adapt
    {
        typedef
            function< detail::baby_adapt<Lambda> >
        type; // = { {} };
    };


    #define PSTADE_EGG_ADAPT_INITIALIZER() \
        { {} } \
    /**/


    // If you are a msvc-8.0 user, prefer this macro.
    #define PSTADE_EGG_ADAPT(L) \
        pstade::egg::adapt<PSTADE_EGG_AS_MPL_LAMBDA(L)>::type \
    /**/


} } // namespace pstade::egg


#endif
