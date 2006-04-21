#ifndef PSTADE_MELON_S_HPP
#define PSTADE_MELON_S_HPP


// PStade.Melon
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser/plus.hpp>
#include <pstade/biscuit/parser/primitive/chset.hpp>
#include "./Char.hpp"


namespace pstade { namespace melon {


template<
    class = void
>
struct S :
    biscuit::plus< biscuit::chset<0x20,0x9,0xD,0xA> >
{ };


} } // namespace pstade::melon


#endif
