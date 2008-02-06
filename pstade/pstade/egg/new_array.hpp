#ifndef PSTADE_EGG_NEW_ARRAY_HPP
#define PSTADE_EGG_NEW_ARRAY_HPP
#include "./detail/prefix.hpp"


// PStade.Egg
//
// Copyright Shunsuke Sogame 2007-2008.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <cstddef> // size_t


namespace pstade { namespace egg {


    template<class T>
    struct X_new_array
    {
        typedef T *result_type;

        T *operator()(std::size_t n) const
        {
            return new T[n];
        }
    };


} } // namespace pstade::egg


#include "./detail/suffix.hpp"
#endif
