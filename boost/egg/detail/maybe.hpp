#ifndef BOOST_EGG_DETAIL_MAYBE_HPP
#define BOOST_EGG_DETAIL_MAYBE_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/mpl/bool.hpp>


namespace boost { namespace egg { namespace details {


    // See: http://www.haskell.org/onlinereport/maybe.html


    struct nothing;

    template<class A>
    struct just;


    template<class Maybe>
    struct is_just :
        mpl::false_
    { };

    template<class A>
    struct is_just< just<A> > :
        mpl::true_
    { };


    template<class Maybe>
    struct is_nothing :
        mpl::false_
    { };

    template< >
    struct is_nothing<nothing> :
        mpl::true_
    { };


    template<class Maybe>
    struct from_just;

    template<class A>
    struct from_just< just<A> >
    {
        typedef A type;
    };


    template<class D, class Maybe>
    struct from_maybe;

    template<class D, class A>
    struct from_maybe< D, just<A> >
    {
        typedef A type;
    };

    template<class D>
    struct from_maybe< D, nothing >
    {
        typedef D type;
    };


} } } // namespace boost::egg::details


#endif
