#ifndef PSTADE_DEDUCED_CONST_HPP
#define PSTADE_DEDUCED_CONST_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// If 'T' is deduced as array type,
// VC7.1 type system is broken by the syntax 'T const'.
// So prefer 'boost::add_const', or
// you can use this macro to say the bug loudly!
//
// See also <pstade/egg/detail/msvc71_result_of.hpp>.


#include <pstade/boost_workaround.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, == 1310) // VC7.1

    #include <boost/type_traits/add_const.hpp>

    // Workaround:
    // Never write '::boost'; VC7.1 would show more weird behavior.
    #define PSTADE_DEDUCED_CONST(T) \
        typename boost::add_const< T >::type \
    /**/

#else

    #define PSTADE_DEDUCED_CONST(T) \
        T const \
    /**/

#endif


#endif
