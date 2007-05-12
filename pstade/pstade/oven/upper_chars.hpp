#ifndef PSTADE_OVEN_UPPER_CHARS_HPP
#define PSTADE_OVEN_UPPER_CHARS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cctype> // toupper
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include "./detail/xxx_chars.hpp"


namespace pstade { namespace oven {
    
    
namespace upper_chars_detail {


    struct to_upper :
        callable<to_upper>
    {
        template< class Myself, class CharT, class Locale >
        struct apply
        {
            typedef CharT type;
        };

        template< class Result, class CharT >
        Result call(CharT ch, std::locale const& loc) const
        {
            return std::toupper(ch, loc);
        }
    };


} // namespace upper_chars_detail


typedef detail::xxx_chars<upper_chars_detail::to_upper> op_make_upper_chars;
PSTADE_CONSTANT(make_upper_chars, (op_make_upper_chars))
PSTADE_PIPABLE(upper_chars, (op_make_upper_chars))


} } // namespace pstade::oven


#endif

