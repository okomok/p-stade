#if defined(_MSC_VER)
#pragma once


// PStade.Vodka
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#if (_MSC_VER >= 1400)
    #if defined(_SCL_SECURE_NO_DEPRECATE)
        #undef _SCL_SECURE_NO_DEPRECATE
    #endif

    #if defined(_CRT_SECURE_NO_DEPRECATE)
        #undef _CRT_SECURE_NO_DEPRECATE
    #endif
#endif


#pragma warning(pop)


#endif
