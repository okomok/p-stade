#ifndef PSTADE_MELON_PROLOG_HPP
#define PSTADE_MELON_PROLOG_HPP


// PStade.Melon
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser/opt.hpp>
#include <pstade/biscuit/parser/seq.hpp>
#include <pstade/biscuit/parser/star.hpp>
#include "./doctypedecl.hpp"
#include "./Misc.hpp"
#include "./XMLDecl.hpp"
#include "./detail/if_default.hpp"


namespace pstade { namespace melon {


template<
    class XMLDecl_ = default_,
    class Misc_ = default_,
    class doctypedecl_ = default_
>
struct prolog :
    biscuit::seq<
        biscuit::opt<typename detail::if_default<XMLDecl<>, XMLDecl_>::type>,
        biscuit::star<typename detail::if_default<Misc<>, Misc_>::type>,
        biscuit::opt<
            biscuit::seq<
                typename detail::if_default<doctypedecl<>, doctypedecl_>::type,
                biscuit::star<typename detail::if_default<Misc<>, Misc_>::type>
            >
        >
    >
{ };


} } // namespace pstade::melon


#endif
