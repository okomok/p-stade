#ifndef PSTADE_OVEN_COPIED_HPP
#define PSTADE_OVEN_COPIED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/automatic.hpp>
#include <pstade/pipable.hpp>
#include "./copy_range.hpp"


namespace pstade { namespace oven {


PSTADE_AUTOMATIC(make_copied, (op_copy_range<_>))
PSTADE_PIPABLE(copied, (op_make_copied))


} } // namespace pstade::oven



#endif
