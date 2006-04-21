#ifndef PSTADE_MELON_MISC_HPP
#define PSTADE_MELON_MISC_HPP


// PStade.Melon
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser/or.hpp>
#include "./Comment.hpp"
#include "./PI.hpp"
#include "./S.hpp"
#include "./detail/if_default.hpp"


namespace pstade { namespace melon {


template<
    class Comment_ = default_,
    class PI_ = default_,
    class S_ = default_
>
struct Misc :
    biscuit::or_<
        typename detail::if_default<Comment<>, Comment_>::type,
        typename detail::if_default<PI<>, PI_>::type,
        typename detail::if_default<S<>, S_>::type
    >
{ };


} } // namespace pstade::melon


#endif
