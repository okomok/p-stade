

// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// (C) Copyright Ion Gaztanaga 2005-2008. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef PSTADE_DETAIL_SUPPRESS_WARNING_BEGIN_INCLUDE_HPP
#define PSTADE_DETAIL_SUPPRESS_WARNING_BEGIN_INCLUDE_HPP
#include <boost/config.hpp>
#endif


#if defined(BOOST_MSVC)

    #pragma warning(push)

    #pragma warning(disable: 4180) // qualifier applied to function type has no meaning; ignored
    #pragma warning(disable: 4510) // default constructor could not be generated
    #pragma warning(disable: 4511) // copy constructor could not be generated
    #pragma warning(disable: 4512) // assignment operator could not be generated
    #pragma warning(disable: 4610) // T can never be instantiated - user defined constructor required
    #pragma warning(disable: 4675) // resolved overload was found by argument-dependent lookup
    #pragma warning(disable: 4819) // character that cannot be represented in the current code page

    #pragma inline_recursion(on) // turn on inline recursion
    #pragma inline_depth(255) // max inline depth

    #if !defined(_SCL_SECURE_NO_DEPRECATE)
        #define _SCL_SECURE_NO_DEPRECATE
        #define PSTADE_SCL_SECURE_NO_DEPRECATE
    #endif

    #if !defined(_CRT_SECURE_NO_DEPRECATE)
        #define _CRT_SECURE_NO_DEPRECATE
        #define PSTADE_CRT_SECURE_NO_DEPRECATE
    #endif

#endif
