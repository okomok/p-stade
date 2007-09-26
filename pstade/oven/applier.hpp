#ifndef PSTADE_OVEN_APPLIER_HPP
#define PSTADE_OVEN_APPLIER_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pass_by.hpp>
#include "./detail/base_to_adaptor.hpp"
#include "./detail/function_output_iterator.hpp"


namespace pstade { namespace oven {


namespace applier_detail {


    template< class UnaryFun >
    struct base
    {
        typedef
            detail::function_output_iterator<
                typename pass_by_value<UnaryFun>::type
            >
        result_type;

        result_type operator()(UnaryFun& fun) const
        {
            return result_type(fun);
        }
    };


} // namespace applier_detail


PSTADE_OVEN_BASE_TO_ADAPTOR(applier, (applier_detail::base<_>))


} } // namespace pstade::oven


#endif
