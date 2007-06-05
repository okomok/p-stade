#ifndef PSTADE_NONCONSTRUCTIBLE_HPP
#define PSTADE_NONCONSTRUCTIBLE_HPP
#include "./prelude.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// See:
//
// http://lists.boost.org/Archives/boost/2000/05/3135.php
// http://lists.boost.org/Archives/boost/2006/07/108310.php


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
