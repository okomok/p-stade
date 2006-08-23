#ifndef PSTADE_NONCONSTRUCTIBLE_HPP
#define PSTADE_NONCONSTRUCTIBLE_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/adl_barrier.hpp>


namespace pstade {

PSTADE_ADL_BARRIER(nonconstructible) {


struct nonconstructible
{
private:
    nonconstructible();
};


} // ADL barrier

} // namespace pstade


#endif
