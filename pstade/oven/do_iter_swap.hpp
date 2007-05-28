#ifndef PSTADE_OVEN_DO_ITER_SWAP_HPP
#define PSTADE_OVEN_DO_ITER_SWAP_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./detail/prelude.hpp"
#include <algorithm> // iter_swap
#include <pstade/constant.hpp>


namespace pstade { namespace oven {


struct op_do_iter_swap
{
    typedef void result_type;

    template< class Iterator >
    void operator()(Iterator left, Iterator right) const
    {
        using std::iter_swap;
        iter_swap(left, right);
    }
};


PSTADE_CONSTANT(do_iter_swap, (op_do_iter_swap))


} } // namespace pstade::oven


#endif
