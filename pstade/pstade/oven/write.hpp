#ifndef PSTADE_OVEN_WRITE_HPP
#define PSTADE_OVEN_WRITE_HPP
#include "./detail/prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/pod_constant.hpp>


namespace pstade { namespace oven {


struct T_write
{
    typedef void result_type;

    template< class WritableIterator, class X >
    void operator()(WritableIterator it, X& x) const
    {
        *it = x;
    }

    template< class WritableIterator, class X >
    void operator()(WritableIterator it, X const& x) const
    {
        *it = x;
    }
};


PSTADE_POD_CONSTANT((T_write), write) = {};


} } // namespace pstade::oven


#endif
