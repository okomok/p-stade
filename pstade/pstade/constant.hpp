#ifndef PSTADE_CONSTANT_HPP
#define PSTADE_CONSTANT_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Copyright David Abrahams 2006. Distributed under the Boost 
// Software License, Version 1.0. (See accompanying 
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt) 


//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/in_unnamed.hpp>
#include <pstade/singleton.hpp>
#include <pstade/unparenthesize.hpp>


#define PSTADE_CONSTANT(O, T) \
    PSTADE_CONSTANT_aux(O, PSTADE_UNPARENTHESIZE(T)) \
/**/

    #define PSTADE_CONSTANT_aux(O, T) \
        namespace { \
            PSTADE_IN_UNNAMED T const& O = ::pstade::singleton< T >::instance; \
        } \
    /**/


#define PSTADE_CONSTANT_FWD(O, T) \
    PSTADE_CONSTANT_FWD_aux(O, PSTADE_UNPARENTHESIZE(T)) \
/**/

    #define PSTADE_CONSTANT_FWD_aux(O, T) \
        namespace { \
            extern T const& O; \
        } \
    /**/


#endif
