#ifndef PSTADE_EGG_MAKE_HPP
#define PSTADE_EGG_MAKE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/baby_make.hpp"
#include "./function.hpp"


namespace pstade { namespace egg {


    template<class X>
    struct xp_make
    {
        typedef
            function< detail::baby_make<X> >
        type;
    };


} } // namespace pstade::egg


#endif
