#ifndef PSTADE_IMPLIES_HPP
#define PSTADE_IMPLIES_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade {


inline
bool implies(bool p, bool q)
{
    return !p || q;
}


} // namespace pstade


#endif
