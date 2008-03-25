#ifndef BOOST_EGG_DETAIL_UNREF_HPP
#define BOOST_EGG_DETAIL_UNREF_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/function_fwd.hpp>
#include <boost/egg/detail/pass_by_value.hpp>


namespace boost { namespace egg { namespace details {


    template<class Bytag, class A>
    struct unref;


    // rvalue
    template<class A>
    struct unref<by_perfect, A>
    {
        typedef A const type;
    };

    // lvalue
    template<class A>
    struct unref<by_perfect, A &>
    {
        typedef A type;
    };


    // Notice const-qualified rvalue can be passed,
    // and cv-qualifier is ignored in function parameter list.
    template<class A>
    struct unref<by_ref, A> :
        unref<by_perfect, A>
    { };


    // rvalue
    template<class A>
    struct unref<by_cref, A>
    {
        typedef A const type;
    };

    // lvalue
    template<class A>
    struct unref<by_cref, A &>
    {
        typedef A const type;
    };


    // always non-const for movable types.
    template<class A>
    struct unref<by_value, A> :
        pass_by_value<A>
    { };


} } } // namespace boost::egg::details


#endif
