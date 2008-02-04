#ifndef PSTADE_DERIVED_FROM_HPP
#define PSTADE_DERIVED_FROM_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade {


    template<class Base>
    struct derived_from :
        Base
    {
        typedef Base base_class;
    };


} // namespace pstade


#endif
