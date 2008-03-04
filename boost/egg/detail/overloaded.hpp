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

    namespace boost { namespace egg { namespace details {
        template<class Re>
        struct overloaded { };
    } } }


#else


#endif


#endif
