#ifndef PSTADE_MELON_DOCUMENT_HPP
#define PSTADE_MELON_DOCUMENT_HPP


// PStade.Melon
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser/seq.hpp>
#include <pstade/biscuit/parser/star.hpp>
#include "./element.hpp"
#include "./Misc.hpp"
#include "./prolog.hpp"
#include "./detail/if_default.hpp"


namespace pstade { namespace melon {


template<
    class element_,
    class prolog_ = default_,
    class Misc_ = default_
>
struct document :
    biscuit::seq<
        typename detail::if_default<prolog<>, prolog_>::type,
        element_,
        biscuit::star<
            typename detail::if_default<Misc<>, Misc_>::type
        >
    >
{ };


} } // namespace pstade::melon


#endif
