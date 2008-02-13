#ifndef PSTADE_EGG_POLY_HPP
#define PSTADE_EGG_POLY_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/placeholders.hpp> // inclusion guaranteed
#include "./detail/before_mpl_apply.hpp"
#include "./detail/little_poly.hpp"
#include "./by_perfect.hpp"


namespace pstade { namespace egg {


    template<class Expr, class Strategy = by_perfect, class NullaryResult = boost::use_default>
    struct poly
    {
        typedef
            function<detail::little_poly<PSTADE_EGG_BEFORE_MPL_APPLY_TPL(Expr), NullaryResult>, Strategy>
        type;
    };

    #define PSTADE_EGG_POLY() {{}}


} } // namespace pstade::egg


#include "./detail/suffix.hpp"
#endif
