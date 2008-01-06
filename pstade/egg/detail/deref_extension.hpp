#ifndef PSTADE_EGG_DETAIL_DEREF_EXTENSION_HPP
#define PSTADE_EGG_DETAIL_DEREF_EXTENSION_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/indirect_reference.hpp>
#include <boost/optional/optional_fwd.hpp>
#include "../extension_fwd.hpp"


namespace pstade_egg_extension {


    template<class X>
    struct Dereferenceable
    {
        typedef typename
            boost::indirect_reference<X>::type
        reference;
    };


    // boost::optional
    //

    template<class T>
    struct Dereferenceable< boost::optional<T> >
    {
        typedef T& reference;
    };

    template<class T>
    struct Dereferenceable< boost::optional<T> const >
    {
        typedef T const& reference;
    };

    template<class T>
    struct Dereferenceable< boost::optional<T&> >
    {
        typedef T& reference;
    };

    template<class T>
    struct Dereferenceable< boost::optional<T&> const >
    {
        typedef T& reference;
    };


} // namespace pstade_egg_extension


#endif
