#ifndef PSTADE_EGG_TO_LOWER_HPP
#define PSTADE_EGG_TO_LOWER_HPP


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <locale> // tolower
#include "./detail/char_conversion.hpp"


namespace pstade { namespace egg {

    #define  PSTADE_EGG_CHAR_CONVERSION_PARAMS (to_lower, std::tolower)
    #include PSTADE_EGG_CHAR_CONVERSION()

} } // namespace pstade::egg


#endif
