#ifndef PSTADE_MELON_CDSECT_HPP
#define PSTADE_MELON_CDSECT_HPP


// PStade.Melon
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser/seq.hpp>
#include "./CData.hpp"
#include "./CDEnd.hpp"
#include "./CDStart.hpp"
#include "./detail/if_default.hpp"


namespace pstade { namespace melon {


template<
    class CDStart_ = default_,
    class CData_ = default_,
    class CDEnd_ = default_
>
struct CDSect :
    biscuit::seq<
        typename detail::if_default<CDStart<>, CDStart_>::type,
        typename detail::if_default<CData<>, CData_>::type,
        typename detail::if_default<CDEnd<>, CDEnd_>::type
    >
{ };


} } // namespace pstade::melon


#endif
