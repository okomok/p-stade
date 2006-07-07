#ifndef PSTADE_OVEN_DETAIL_NOT_EQUAL_TO_HPP
#define PSTADE_OVEN_DETAIL_NOT_EQUAL_TO_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/instance.hpp>


namespace pstade { namespace oven { namespace detail {


struct not_equal_to_fun
{
    typedef bool result_type;

    template< class X, class Y >
    bool operator()(X const& x, Y const& y) const
    {
        return x != y;
    }
};


PSTADE_INSTANCE(not_equal_to_fun const, not_equal_to, value)


} } } // namespace pstade::oven::detail


#endif
