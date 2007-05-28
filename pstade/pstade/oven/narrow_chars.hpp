#ifndef PSTADE_OVEN_NARROW_CHARS_HPP
#define PSTADE_OVEN_NARROW_CHARS_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/prelude.hpp"
#include <locale>
#include <pstade/callable.hpp>
#include <pstade/constant.hpp>
#include <pstade/pipable.hpp>
#include "./detail/xxx_chars.hpp"


namespace pstade { namespace oven {
    
    
namespace narrow_chars_detail {


    struct to_narrow :
        callable<to_narrow>
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


} // namespace narrow_chars_detail


typedef detail::xxx_chars<narrow_chars_detail::to_narrow> op_make_narrow_chars;
PSTADE_CONSTANT(make_narrow_chars, (op_make_narrow_chars))
PSTADE_PIPABLE(narrow_chars, (op_make_narrow_chars))


} } // namespace pstade::oven


#endif
