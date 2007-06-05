#ifndef PSTADE_DONT_CARE_HPP
#define PSTADE_DONT_CARE_HPP
#include "./prelude.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Ported from Boost.Accumulators
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


namespace pstade {


    struct dont_care
    {
        template<class T>
        dont_care(T const&)
        { }
    };


} // namespace pstade


#endif
