#ifndef PSTADE_EGG_DETAIL_TO_BOOL_HPP
#define PSTADE_EGG_DETAIL_TO_BOOL_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace egg { namespace detail {


    template<class X> inline
    bool to_bool(X const& x)
    {
        // Suppress a msvc warning;
        // If `X` has overloaded operators, `!!` seems more preferable than `!= 0`.
        return !!x;
    }


} } } // namespace pstade::egg::detail


#endif
