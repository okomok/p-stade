#ifndef PSTADE_COPY_CONSTRUCT_HPP
#define PSTADE_COPY_CONSTRUCT_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/callable.hpp>
#include <pstade/specified.hpp>


namespace pstade {


    template<class To>
    struct op_copy_construct :
        callable< op_copy_construct<To> >
    {
        template<class Myself, class From>
        struct apply
        {
            typedef To type;
        };

        template<class Result, class From>
        Result call(From& from) const
        {
            return from;
        }
    };


    PSTADE_SPECIFIED1(copy_construct, op_copy_construct, 1)


} // namespace pstade


#endif
