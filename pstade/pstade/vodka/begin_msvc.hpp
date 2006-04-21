#if defined(_MSC_VER)
#pragma once


// PStade.Vodka
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#pragma warning(push)


// inline aggressively
#pragma inline_recursion(on) // turn on inline recursion
#pragma inline_depth(255) // max inline depth


#if (_MSC_VER < 1400)
    #pragma warning(disable: 4511) // copy constructor could not be generated
    #pragma warning(disable: 4512) // assignment operator could not be generated
    #pragma warning(disable: 4675) // resolved overload was found by argument-dependent lookup
#endif


#if (_MSC_VER >= 1400)
    #pragma warning(disable: 4819) // character that cannot be represented in the current code page

    #if !defined(_SCL_SECURE_NO_DEPRECATE)
        #define _SCL_SECURE_NO_DEPRECATE
    #endif

    #if !defined(_CRT_SECURE_NO_DEPRECATE)
        #define _CRT_SECURE_NO_DEPRECATE
    #endif
#endif


#endif
