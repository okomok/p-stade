#ifndef PSTADE_MELON_EXTENDER_HPP
#define PSTADE_MELON_EXTENDER_HPP


// PStade.Melon
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser/or.hpp>
#include <pstade/biscuit/parser/primitive/bchseq.hpp>
#include "./ucs4_t.hpp"


namespace pstade { namespace melon {


template<
    class = void
>
struct Extender :
    biscuit::or_<
        biscuit::bchseq<ucs4_t, 0x00B7>, biscuit::bchseq<ucs4_t, 0x02D0>,
        biscuit::bchseq<ucs4_t, 0x02D1>, biscuit::bchseq<ucs4_t, 0x0387>

        // too many
        //

    >
{ };


} } // namespace pstade::melon


#endif
