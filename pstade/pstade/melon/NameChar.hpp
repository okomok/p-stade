#ifndef PSTADE_MELON_NAMECHAR_HPP
#define PSTADE_MELON_NAMECHAR_HPP


// PStade.Melon
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser/or.hpp>
#include <pstade/biscuit/parser/primitive/chseq.hpp>
#include "./CombiningChar.hpp"
#include "./Extender.hpp"
#include "./Digit.hpp"
#include "./Letter.hpp"
#include "./detail/if_default.hpp"


namespace pstade { namespace melon {


template<
    class Letter_ = default_,
    class Digit_ = default_,
    class CombiningChar_ = default_,
    class Extender_ = default_
>
struct NameChar :
    biscuit::or_<
        typename detail::if_default<Letter<>, Letter_>::type,
        typename detail::if_default<Digit<>, Digit_>::type,
        biscuit::chseq<'.'>, biscuit::chseq<'-'>,
        biscuit::chseq<'_'>, biscuit::chseq<':'>,
        typename detail::if_default<CombiningChar<>, CombiningChar_>::type,
        typename detail::if_default<Extender<>, Extender_>::type
    >
{ };


} } // namespace pstade::melon


#endif
