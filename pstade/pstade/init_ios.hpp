#ifndef PSTADE_INIT_IOS_HPP
#define PSTADE_INIT_IOS_HPP


// PStade.Wine
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Without this, the standard doesn't guarantee
// 'std::cout' etc is initialized before 'main'.


#include <ios> // ios_base::Init
#include <pstade/instance.hpp>


namespace pstade { namespace init_ios_detail {


PSTADE_INSTANCE(std::ios_base::Init const, init, value)


} } // namespace pstade::init_ios_detail


#endif
