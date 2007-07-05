#ifndef PSTADE_EGG_NEW_ARRAY_HPP
#define PSTADE_EGG_NEW_ARRAY_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t


namespace pstade { namespace egg {


    template<class X>
    struct tp_new_array
    {
        struct type
        {
            typedef X *result_type;

            X *operator()(std::size_t n) const
            {
                return new X[n];
            }
        };
    };


    template<class X>
    struct xp_new_array :
        tp_new_array<X>::type
    { };


} } // namespace pstade::egg


#endif
