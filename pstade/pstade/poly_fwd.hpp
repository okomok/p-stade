#ifndef PSTADE_POLY_FWD_HPP
#define PSTADE_POLY_FWD_HPP
#include "./detail/prefix.hpp"


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade {


    template<class O>
    struct poly;


    // You can specialize this.
    template<class O>
    struct poly_storage_size;


#if !defined(PSTADE_POLY_MIN_STORAGE_SIZE)
    #define PSTADE_POLY_MIN_STORAGE_SIZE 128
#endif

#if !defined(PSTADE_POLY_MAX_STORAGE_SIZE)
    #define PSTADE_POLY_MAX_STORAGE_SIZE 512
#endif
    

} // namespace pstade


#endif
