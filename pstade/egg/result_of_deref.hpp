#ifndef PSTADE_EGG_RESULT_OF_DEREF_HPP
#define PSTADE_EGG_RESULT_OF_DEREF_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/indirect_reference.hpp>
#include <boost/optional/optional_fwd.hpp>
#include "./result_of_deref_fwd.hpp"


namespace pstade { namespace egg {


    template<class X>
    struct result_of_deref
    {
        typedef typename
            pstade_egg_extension::Dereferenceable<X>::reference
        type;
    };


} } // namespace pstade::egg


namespace pstade_egg_extension {


    template<class X>
    struct Dereferenceable
    {
        typedef typename
            boost::indirect_reference<X>::type
        reference;
    };

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


    // boost::optional
    //

    template<class T>
    struct Dereferenceable< boost::optional<T> >
    {
        typedef T& reference;
    };

    template<class T>
    struct Dereferenceable< boost::optional<T&> >
    {
        typedef T& reference;
    };

    template<class T>
    struct Dereferenceable< boost::optional<T> const >
    {
        typedef T const& reference;
    };

    template<class T>
    struct Dereferenceable< boost::optional<T&> const >
    {
        typedef T& reference;
    };


} // namespace pstade_egg_extension


#endif
