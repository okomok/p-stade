#ifndef PSTADE_POD_CONSTANT_HPP
#define PSTADE_POD_CONSTANT_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// After all, ODR violation workaround:
//   http://lists.boost.org/Archives/boost/2007/06/123353.php
// was given up.
// Even gcc is broken around "address constant expression".


#include <pstade/ignore_unused.hpp>
#include <pstade/pod_assert.hpp>
#include <pstade/unparenthesize.hpp>


#define PSTADE_POD_CONSTANT(F, O) \
    PSTADE_POD_ASSERT_OF(F, O); \
    PSTADE_UNPARENTHESIZE(F) const PSTADE_IGNORE_UNUSED O
/**/


#endif
