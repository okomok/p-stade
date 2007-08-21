#ifndef PSTADE_OVEN_IN_BLOCK_HPP
#define PSTADE_OVEN_IN_BLOCK_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/egg/deferred.hpp>
#include <pstade/pass_by.hpp>
#include <pstade/pod_constant.hpp>
#include "./detail/block_iterator.hpp"
#include "./iter_range.hpp"


namespace pstade { namespace oven {


namespace in_block_detail {


    template< class IteratorBlock >
    struct base
    {
        typedef
            detail::block_iterator<
                typename pass_by_value<IteratorBlock>::type
            >
        iter_t;

        typedef
            iter_range<iter_t> const
        result_type;

        result_type operator()(IteratorBlock& b) const
        {
            return result_type(iter_t(b), iter_t());
        }
    };


} // namespace in_block_detail


typedef PSTADE_EGG_DEFER((in_block_detail::base<boost::mpl::_>)) op_in_block;
PSTADE_POD_CONSTANT((op_in_block), in_block) = PSTADE_EGG_DEFERRED;


} } // namespace pstade::oven


#endif
