#ifndef PSTADE_OVEN_UPPER_CHARS_HPP
#define PSTADE_OVEN_UPPER_CHARS_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cctype> // toupper
#include "./detail/little_to_adaptor.hpp"
#include "./detail/xxx_chars.hpp"


namespace pstade { namespace oven {
    
    
namespace upper_chars_detail {


    struct little_to
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


    typedef egg::function<little_to> to;


} // namespace upper_chars_detail


PSTADE_OVEN_LITTLE_TO_ADAPTOR(upper_chars, (detail::xxx_chars<upper_chars_detail::to>::little))


} } // namespace pstade::oven


#endif

