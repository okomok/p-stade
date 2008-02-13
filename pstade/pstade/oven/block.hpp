#ifndef PSTADE_OVEN_BLOCK_HPP
#define PSTADE_OVEN_BLOCK_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/poly.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pod_constant.hpp>
#include "./detail/block_iterator.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace block_detail {


    template< class IterationBlock >
    struct base
    {
        typedef
            detail::block_iterator<
                typename pass_by_value<IterationBlock>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(IterationBlock& b) const
        {
            return result_type(iter_t(b), iter_t());
        }
    };


} // namespace block_detail


typedef egg::poly< block_detail::base<boost::mpl::_> >::type T_block;
PSTADE_POD_CONSTANT((T_block), block) = PSTADE_EGG_POLY();


} } // namespace pstade::oven


#endif
