#ifndef PSTADE_OVEN_ITER_OPERATIONS_HPP
#define PSTADE_OVEN_ITER_OPERATIONS_HPP
#include "./prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/function.hpp>


namespace pstade { namespace oven {


namespace iter_operations {


    template< class Iterator >
    struct baby_pre_inc
    {
        typedef Iterator& result_type;

        result_type operator()(Iterator& it) const
        {
            return ++it;
        }
    };


    template< class Iterator >
    struct baby_pre_dec
    {
        typedef Iterator& result_type;

        result_type operator()(Iterator& it) const
        {
            return --it;
        }
    };


    template< class Iterator >
    struct baby_plus_assign
    {
        typedef Iterator& result_type;

        result_type operator()(Iterator& it) const
        {
            return it += n;
        }
    };


} // namespace iter_operations_detail


PSTADE_FUNCTION(iter_pre_inc, (iter_operations_detail::baby_pre_inc<_>))
PSTADE_FUNCTION(iter_pre_dec, (iter_operations_detail::baby_pre_dec<_>))
PSTADE_FUNCTION(iter_plus_assign, (iter_operations_detail::baby_pre_plus_assign<_>))


} } // namespace pstade::oven


#endif
