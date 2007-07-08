#ifndef PSTADE_OVEN_LOWER_CHARS_HPP
#define PSTADE_OVEN_LOWER_CHARS_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cctype> // tolower
#include "./detail/baby_to_adaptor.hpp"
#include "./detail/xxx_chars.hpp"


namespace pstade { namespace oven {
    
    
namespace lower_chars_detail {


    struct baby_to
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


    typedef egg::function<baby_to> to;


} // namespace lower_chars_detail


PSTADE_OVEN_BABY_TO_ADAPTOR(lower_chars, (detail::xxx_chars<lower_chars_detail::to>::baby))


} } // namespace pstade::oven


#endif
