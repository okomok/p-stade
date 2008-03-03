#ifndef BOOST_EGG_DETAIL_OVERLOADED_HPP
#define BOOST_EGG_DETAIL_OVERLOADED_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/boost_workaround.hpp>

#if BOOST_WORKAROUND(__GNUC__, == 3)
    #define BOOST_EGG_NEEDS_OVERLOADED
    #include <boost/egg/detail/enable_if.hpp>
    #include <boost/egg/detail/has_xxx.hpp>
#endif


namespace boost { namespace egg { namespace details {


#if defined(BOOST_EGG_NEEDS_OVERLOADED)

    template<class Re>
    struct overloaded { };

    BOOST_EGG_HAS_XXX(boost_egg_overloaded)

    #define BOOST_EGG_OVERLOADED_PREAMBLE() typedef void boost_egg_overloaded;
    #define BOOST_EGG_OVERLOADED(R) boost::egg::details::overloaded< R >, 

#else

    #define BOOST_EGG_OVERLOADED_PREAMBLE()
    #define BOOST_EGG_OVERLOADED(R)

#endif


} } } // namespace boost::egg::details


#endif
