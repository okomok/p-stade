#ifndef PSTADE_DONT_CARE_HPP
#define PSTADE_DONT_CARE_HPP
#include "./detail/prefix.hpp"


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


#include <pstade/boost_workaround.hpp>


namespace pstade {


    struct dont_care
    {
        template<class X>
        dont_care(X const&)
        { }

#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1500))
        dont_care(int const&)
        { }
#endif
    };


} // namespace pstade


#endif
