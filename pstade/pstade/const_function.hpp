#ifndef PSTADE_CONST_FUNCTION_HPP
#define PSTADE_CONST_FUNCTION_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// 'boost::result_of<const function-pointer(..)>' doesn't work.
// It seems a bug, function behavior shouldn't be affected by 'const', though.
// Anyway, wrap a function type which can be a pointer by this macro...


#if 1
    #define PSTADE_CONST_FUNCTION(F) F
#else
    // Someday...
    #define PSTADE_CONST_FUNCTION(F) F const
#endif


#endif
