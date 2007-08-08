#ifndef PSTADE_EGG_ENVELOPE_HPP
#define PSTADE_EGG_ENVELOPE_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// What:
//
// Use this instead of 'boost::type<>'
// if you want to cry out a bug of gcc-3.4 overload resolution.
// See <pstade/const_overloaded.hpp> in detail.


namespace pstade { namespace egg {


    template<class T>
    struct envelope { };


} } // namespace pstade::egg


#endif
