#ifndef PSTADE_DO_SWAP_HPP
#define PSTADE_DO_SWAP_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Copyright 2005, 2006 Cryolite.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <algorithm> // swap
#include <pstade/constant.hpp>


namespace pstade {


    struct op_do_swap
    {
        typedef void result_type;

        template<class T>
        void operator()(T& a, T& b) const
        {
            using std::swap;
            swap(a, b);
        }
    };


    PSTADE_CONSTANT(do_swap, (op_do_swap))


} // namespace pstade


#endif
