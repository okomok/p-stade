#ifndef PSTADE_CAST_FUNCTION_HPP
#define PSTADE_CAST_FUNCTION_HPP


// PStade.Wine
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Pending...
//


#include <boost/utility/result_of.hpp>
#include <pstade/const_overloaded.hpp>
#include <pstade/deduced_const.hpp>


#define PSTADE_CAST_FUNCTION(Name, Op, Param) \
    template<Param pstade_To, class pstade_From> inline \
    typename ::boost::result_of<Op<pstade_To>(pstade_From&)>::type \
    Name(pstade_From& from PSTADE_CONST_OVERLOADED(pstade_From)) \
    { \
        return Op<pstade_To>()(from); \
    } \
    \
    template<Param pstade_To, class pstade_From> inline \
    typename ::boost::result_of<Op<pstade_To>(PSTADE_DEDUCED_CONST(pstade_From)&)>::type \
    Name(pstade_From const& from) \
    { \
        return Op<pstade_To>()(from); \
    } \
/**/


#endif
