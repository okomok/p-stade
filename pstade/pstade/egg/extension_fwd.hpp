#ifndef PSTADE_EGG_EXTENSION_FWD_HPP
#define PSTADE_EGG_EXTENSION_FWD_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade_egg_extension {


    template<class X>
    struct ForwardingStrategy;


    template<class X>
    struct Dereferenceable;

    template<class X>
    struct Dereferenceable<X const> :
        Dereferenceable<X>
    { };

    template<class X>
    struct Dereferenceable<X volatile> :
        Dereferenceable<X>
    { };

    template<class X>
    struct Dereferenceable<X const volatile> :
        Dereferenceable<X>
    { };


} // namespace pstade_egg_extension


#endif
