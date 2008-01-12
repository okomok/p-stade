#ifndef BOOST_EGG_DETAIL_PREFIX_HPP
#define BOOST_EGG_DETAIL_PREFIX_HPP


// Boost.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if 1

    namespace pstade {
        namespace egg { }
    }

    namespace boost {
        namespace egg = pstade::egg;
    }

#endif


#ifdef _MSC_VER
    #pragma inline_recursion(on)
    #pragma inline_depth(255)
#endif


#endif
