#ifndef PSTADE_OVEN_SHARED_REGULAR_HPP
#define PSTADE_OVEN_SHARED_REGULAR_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//
// This is considered as a generalized 'regular_c'.


#include <pstade/function.hpp>
#include <pstade/result_of.hpp>
#include <pstade/to_shared_ptr.hpp>
#include "./detail/indirect_function.hpp"


namespace pstade { namespace oven {


namespace shared_regular_detail {


    template< class Ptr >
    struct baby
    {
        typedef typename
            result_of<op_to_shared_ptr<>(Ptr&)>::type
        sp_t;

        typedef
            detail::indirect_function<sp_t>
        result_type;

        result_type operator()(Ptr& pf) const
        {
            return result_type(to_shared_ptr(pf));
        }
    };


} // namespace shared_regular_detail


PSTADE_FUNCTION(shared_regular, (shared_regular_detail::baby<_>))


} } // namespace pstade::oven


#endif
