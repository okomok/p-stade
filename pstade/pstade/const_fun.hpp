#ifndef PSTADE_CONST_FUN_HPP
#define PSTADE_CONST_FUN_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Works around a bug that 'boost::result_of<const function-pointer(..)>' doesn't work.
// If a function object may be a pointer, use this macro...


#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_pointer.hpp>


#if 1

    #define PSTADE_CONST_FUN(F) \
        boost::mpl::if_< ::boost::is_pointer< F >, \
            F, F const \
        >::type \
    /**/

    #define PSTADE_CONST_FUN_TPL(F) \
        typename PSTADE_CONST_FUN(F) \
    /**/

#else

    // Someday...
    #define PSTADE_CONST_FUN(F) F const
    #define PSTADE_CONST_FUN_TPL(F) F const

#endif


#endif
