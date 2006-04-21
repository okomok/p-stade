#ifndef PSTADE_MELON_PITARGET_HPP
#define PSTADE_MELON_PITARGET_HPP


// PStade.Melon
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser/minus.hpp>
#include <pstade/biscuit/parser/or.hpp>
#include <pstade/biscuit/parser/seq.hpp>
#include <pstade/biscuit/parser/primitive/chseq.hpp>
#include "./Name.hpp"
#include "./detail/if_default.hpp"


namespace pstade { namespace melon {


template<
    class Name_ = default_
>
struct PITarget :
    biscuit::minus<
        typename detail::if_default<Name<>, Name_>::type,
        biscuit::seq<
            biscuit::or_< biscuit::chseq<'X'>, biscuit::chseq<'x'> >,
            biscuit::or_< biscuit::chseq<'M'>, biscuit::chseq<'m'> >,
            biscuit::or_< biscuit::chseq<'L'>, biscuit::chseq<'l'> >
        >
    >
{ };


} } // namespace pstade::melon


#endif
