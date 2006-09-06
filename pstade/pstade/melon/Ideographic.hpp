#ifndef PSTADE_MELON_IDEOGRAPHIC_HPP
#define PSTADE_MELON_IDEOGRAPHIC_HPP


// PStade.Melon
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser/or.hpp>
#include <pstade/biscuit/parser/primitive/bchrng.hpp>
#include <pstade/biscuit/parser/primitive/bchseq.hpp>
#include <pstade/ustring.hpp> // ucs4_t


namespace pstade { namespace melon {


template<
    class = void
>
struct Ideographic :
    biscuit::or_<
        biscuit::bchrng<ucs4_t, 0x4E00, 0x9FA5>,
        biscuit::bchseq<ucs4_t, 0x3007>,
        biscuit::bchrng<ucs4_t, 0x3021, 0x3029>
    >
{ };


} } // namespace pstade::melon


#endif
