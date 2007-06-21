#ifndef PSTADE_OVEN_DETAIL_DEFAULT_SPACE_HPP
#define PSTADE_OVEN_DETAIL_DEFAULT_SPACE_HPP
#include "../prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace oven { namespace detail {


template< class Value >
struct default_space
{
    // C++0x won't require this?
    static Value value();
};


template< >
struct default_space<char>
{
    static char value()
    {
        return ' ';
    }
};


template< >
struct default_space<wchar_t>
{
    static wchar_t value()
    {
        return L' ';
    }
};


} } } // namespace pstade::oven::detail


#endif
