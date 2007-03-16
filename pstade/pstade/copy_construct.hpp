#ifndef PSTADE_COPY_CONSTRUCT_HPP
#define PSTADE_COPY_CONSTRUCT_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/utility/result_of.hpp>
#include <pstade/callable.hpp>
#include <pstade/const_overloaded.hpp>
#include <pstade/deduced_const.hpp>


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


    template<class To, class From> inline
    typename boost::result_of<op_copy_construct<To>(From&)>::type
    copy_construct(From& from PSTADE_CONST_OVERLOADED(From))
    {
        return op_copy_construct<To>()(from);
    }

    template<class To, class From> inline
    typename boost::result_of<op_copy_construct<To>(PSTADE_DEDUCED_CONST(From)&)>::type
    copy_construct(From const& from)
    {
        return op_copy_construct<To>()(from);
    }


} // namespace pstade


#endif
