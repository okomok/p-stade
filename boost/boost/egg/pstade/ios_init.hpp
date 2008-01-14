#ifndef PSTADE_IOS_INIT_HPP
#define PSTADE_IOS_INIT_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Without this, the standard doesn't guarantee
// 'std::cout' etc is initialized before 'main'.


#include <ios> // ios_base::Init
#include <boost/egg/pstade/constant.hpp>


namespace pstade { namespace ios_init_detail {


PSTADE_CONSTANT(init, (std::ios_base::Init))


} } // namespace pstade::ios_init_detail


#endif
