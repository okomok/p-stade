#ifndef PSTADE_CONSTANT_HPP
#define PSTADE_CONSTANT_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/singleton.hpp>
#include <pstade/unparenthesize.hpp>


#define PSTADE_CONSTANT(O, T) \
    PSTADE_CONSTANT_aux(O, PSTADE_UNPARENTHESIZE(T)) \
/**/

    // 'stdafx.h' sometimes needs 'static'.
    #define PSTADE_CONSTANT_aux(O, T) \
        namespace { \
            static T const& O = ::pstade::singleton< T >::instance; \
        } \
    /**/


#endif
