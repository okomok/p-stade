#ifndef BOOST_EGG_DETAIL_ENABLE_IF_HPP
#define BOOST_EGG_DETAIL_ENABLE_IF_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/enable_if.hpp>
#include <boost/egg/detail/unspecified.hpp>


namespace boost { namespace egg {


    typedef unspecified *enabler;


    template<class Cond, class T = enabler> 
    struct enable_if_ :
        boost::enable_if<Cond, T>
    { };


    template<class Cond, class F> 
    struct lazy_enable_if_ :
        boost::lazy_enable_if<Cond, F>
    { };


    template<class Cond, class T = enabler> 
    struct disable_if_ :
        boost::disable_if<Cond, T>
    { };


    template<class Cond, class F> 
    struct lazy_disable_if_ :
        boost::lazy_disable_if<Cond, F>
    { };


} } // namespace boost::egg


#endif
