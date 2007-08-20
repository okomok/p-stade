#ifndef PSTADE_OVEN_COPIED_HPP
#define PSTADE_OVEN_COPIED_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/automatic.hpp>
#include <pstade/egg/pipable.hpp>
#include <pstade/pod_constant.hpp>
#include "./copy_range.hpp"


namespace pstade { namespace oven {


typedef egg::automatic< xp_copy_range<boost::mpl::_> >::type op_make_copied;
PSTADE_POD_CONSTANT((op_make_copied), make_copied) = PSTADE_EGG_AUTOMATIC_TYPE();

PSTADE_POD_CONSTANT((egg::result_of_pipable<op_make_copied>::type), copied)
    = PSTADE_EGG_PIPABLE(PSTADE_EGG_AUTOMATIC_TYPE)();


} } // namespace pstade::oven


#endif
