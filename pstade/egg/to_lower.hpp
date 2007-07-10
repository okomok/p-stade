#ifndef PSTADE_EGG_TO_LOWER_HPP
#define PSTADE_EGG_TO_LOWER_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <locale> // tolower
#include "./detail/char_conversion.hpp"


namespace pstade { namespace egg {

    PSTADE_EGG_CHAR_CONVERSION(to_lower, std::tolower)

} } // namespace pstade::egg


#endif
