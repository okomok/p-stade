#ifndef PSTADE_WHAT_HPP
#define PSTADE_WHAT_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <string>
#include <pstade/lexical_cast.hpp>
#include <pstade/oven/c_str_range.hpp>
#include <pstade/oven/copy_range.hpp>


namespace pstade {


template< class Range > inline
std::string what(std::string const& tag, Range const& msg)
{
    return
        '<' + tag + '>' +
            oven::copy_range<std::string>(msg) +
        "</" + tag + '>'
    ;
}


inline
std::string what(std::string tag, char const *psz)
{
    return pstade::what(tag, psz|oven::as_c_str);
}


inline
std::string what(std::string const& tag, int n)
{
    return pstade::what(tag, pstade::lexical_cast<std::string>(n));
}


} // namespace pstade


#endif
