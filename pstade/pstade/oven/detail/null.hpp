#ifndef PSTADE_OVEN_DETAIL_NULL_HPP
#define PSTADE_OVEN_DETAIL_NULL_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/instance.hpp>
#include <pstade/unused.hpp>


namespace pstade { namespace oven { namespace detail {


struct null_fun
{
    typedef void result_type;

    template< class X >
    void operator()(X const& x) const
    {
        pstade::unused(x);
    }
};


PSTADE_INSTANCE(null_fun const, null_, value)


} } } // namespace pstade::oven::detail


#endif
