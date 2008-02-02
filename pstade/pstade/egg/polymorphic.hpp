#ifndef PSTADE_EGG_POLYMORPHIC_HPP
#define PSTADE_EGG_POLYMORPHIC_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/placeholders.hpp> // inclusion guaranteed
#include "./detail/as_mpl_lambda.hpp"
#include "./detail/little_polymorphic.hpp"
#include "./detail/mpl_lambda.hpp"
#include "./by_perfect.hpp"


namespace pstade { namespace egg {


    template<class Expr, class Strategy = by_perfect>
    struct polymorphic
    {
        typedef
            function<detail::little_polymorphic<PSTADE_EGG_MPL_LAMBDA(Expr)>, Strategy>
        type;
    };

    #define PSTADE_EGG_POLYMORPHIC() {{}}


    // If you are a msvc-8/9 user, prefer this macro.
    // Note that PSTADE_EGG_AS_MPL_LAMBDA in 'polymorphic' can't work around.
    #define PSTADE_EGG_DEFER(L) \
        pstade::egg::polymorphic<PSTADE_EGG_AS_MPL_LAMBDA(L)>::type \
    /**/

    #define PSTADE_EGG_DEFER_BY(L, Stg) \
        pstade::egg::polymorphic<PSTADE_EGG_AS_MPL_LAMBDA(L), Stg>::type \
    /**/


} } // namespace pstade::egg


#endif
