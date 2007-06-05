#ifndef PSTADE_OVEN_WRITE_HPP
#define PSTADE_OVEN_WRITE_HPP
#include "./prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/constant.hpp>


namespace pstade { namespace oven {


struct op_write
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


PSTADE_CONSTANT(write, (op_write))


} } // namespace pstade::oven


#endif
