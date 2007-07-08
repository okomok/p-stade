#ifndef PSTADE_OVEN_NARROW_CHARS_HPP
#define PSTADE_OVEN_NARROW_CHARS_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <locale>
#include "./detail/baby_to_adaptor.hpp"
#include "./detail/xxx_chars.hpp"


namespace pstade { namespace oven {
    
    
namespace narrow_chars_detail {


    struct baby_to
    {
        template< class Myself, class CharT, class Locale >
        struct apply
        {
            typedef char type;
        };

        template< class Result, class CharT >
        Result call(CharT ch, std::locale const& loc) const
        {
            return std::use_facet< std::ctype<CharT> >(loc).narrow(ch);
        }
    };


    typedef egg::function<baby_to> to;


} // namespace narrow_chars_detail


PSTADE_OVEN_BABY_TO_ADAPTOR(narrow_chars, (detail::xxx_chars<narrow_chars_detail::to>::baby))


} } // namespace pstade::oven


#endif
