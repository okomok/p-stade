#ifndef PSTADE_MELON_CHAR_HPP
#define PSTADE_MELON_CHAR_HPP


// PStade.Melon
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/cstdint.hpp> // uint32_t
#include <pstade/biscuit/parser/primitive/bchrng.hpp>
#include <pstade/biscuit/parser/primitive/bchseq.hpp>
#include "./ucs4_t.hpp"


namespace pstade { namespace melon {


template<
    class = void
>
struct Char :
    biscuit::or_<
        biscuit::bchseq<ucs4_t, 0x9>,
        biscuit::bchseq<ucs4_t, 0xA>,
        biscuit::bchseq<ucs4_t, 0xD>,
        biscuit::bchrng<ucs4_t, 0x20, 0xD7FF>,
        biscuit::bchrng<ucs4_t, 0xE000, 0xFFFD>,
        biscuit::bchrng<ucs4_t, 0x10000, 0x10FFFF>
    >
{ };


} } // namespace pstade::melon


#endif
