#ifndef PSTADE_EGG_DETAIL_WRAP_HPP
#define PSTADE_EGG_DETAIL_WRAP_HPP
#include "./prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace egg { namespace detail {


    template<class Base>
    struct wrap
    {
        Base base;
    };


} } } // namespace pstade::egg::detail


#endif
