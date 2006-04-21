#ifndef PSTADE_MELON_PI_HPP
#define PSTADE_MELON_PI_HPP


// PStade.Melon
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser/opt.hpp>
#include <pstade/biscuit/parser/seq.hpp>
#include <pstade/biscuit/parser/star_before.hpp>
#include <pstade/biscuit/parser/primitive/chseq.hpp>
#include "./Char.hpp"
#include "./S.hpp"
#include "./PITarget.hpp"
#include "./detail/if_default.hpp"


namespace pstade { namespace melon {


template<
    class PITarget_ = default_,
    class S_ = default_,
    class Char_ = default_
>
struct PI :
    biscuit::seq<
        biscuit::chseq<'<','?'>,
        typename detail::if_default<PITarget<>, PITarget_>::type,
        biscuit::opt<
            biscuit::seq<
                typename detail::if_default<S<>, S_>::type,
                biscuit::star_before<
                    typename detail::if_default<Char<>, Char_>::type,
                    biscuit::chseq<'?','>'>
                > 
            >
        >,
        biscuit::chseq<'?','>'>
    >
{ };


} } // namespace pstade::melon


#endif
