#ifndef PSTADE_MELON_CDATA_HPP
#define PSTADE_MELON_CDATA_HPP


// PStade.Melon
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser/primitive/chseq.hpp>
#include <pstade/biscuit/parser/star_before.hpp>
#include "./Char.hpp"
#include "./detail/if_default.hpp"


namespace pstade { namespace melon {


template<
    class Char_ = default_
>
struct CData :
    biscuit::star_before<
        typename detail::if_default<Char<>, Char_>::type,
        biscuit::chseq<']',']','>'>
    >
{ };


} } // namespace pstade::melon


#endif
