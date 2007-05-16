#ifndef PSTADE_OVEN_LOWER_CHARS_HPP
#define PSTADE_OVEN_LOWER_CHARS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cctype> // tolower
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include "./detail/xxx_chars.hpp"


namespace pstade { namespace oven {
    
    
namespace lower_chars_detail {


    struct to_lower :
        callable<to_lower>
    {
        template< class Myself, class CharT, class Locale >
        struct apply
        {
            typedef CharT type;
        };

        template< class Result, class CharT >
        Result call(CharT ch, std::locale const& loc) const
        {
            return std::tolower(ch, loc);
        }
    };


} // namespace lower_chars_detail


typedef detail::xxx_chars<lower_chars_detail::to_lower> op_make_lower_chars;
PSTADE_CONSTANT(make_lower_chars, (op_make_lower_chars))
PSTADE_PIPABLE(lower_chars, (op_make_lower_chars))


} } // namespace pstade::oven


#endif
