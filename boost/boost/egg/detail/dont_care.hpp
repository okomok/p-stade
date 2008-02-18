#ifndef BOOST_EGG_DETAIL_DONT_CARE_HPP
#define BOOST_EGG_DETAIL_DONT_CARE_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Ported from Boost.Accumulators
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#include <boost/egg/detail/boost_workaround.hpp>


namespace boost { namespace egg { namespace details {


    struct dont_care
    {
        template<class X>
        dont_care(X const&)
        { }

#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1500))
        // `foo(dont_care = 0)` form needs this to link.
        dont_care(int const&)
        { }
#endif
    };


} } } // namespace boost::egg::details


#endif
