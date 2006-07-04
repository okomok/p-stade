#ifndef PSTADE_BISCUIT_ACTION_MACRO_HPP
#define PSTADE_BISCUIT_ACTION_MACRO_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// Never use! :^)


#include <pstade/unused.hpp>


#define PSTADE_BISCUIT_ACTION(Name, Body) \
    struct Name \
    { \
        template< class PStadeBiscuitActorDetailRange, class PStadeBiscuitActorDetailUserState> \
        void operator()(PStadeBiscuitActorDetailRange& rng, PStadeBiscuitActorDetailUserState& us) const \
        { \
            pstade::unused(rng, us); \
            Body \
        } \
    }; \
/**/


#endif
