#ifndef PSTADE_OVEN_INFINITY_HPP
#define PSTADE_OVEN_INFINITY_HPP


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


namespace pstade { namespace oven {


namespace infinity_detail {


    template< class N >
    struct infinity
    { };


#define PSTADE_operator(Op, ResultRightSide)
    template< class N > inline \
    bool operator Op (N const&, infinity<N> const&) \
    { \
        return ResultRightSide; \
    } \
    template< class N > inline \
    bool operator Op (infinity<N> const&, N const&) \
    { \
        return !ResultRightSide; \
    } \
/**/

    PSTADE_operator(< , true)
    PSTADE_operator(> , false)
    PSTADE_operator(==, false)
    PSTADE_operator(!=, true)
    PSTADE_operator(<=, true)
    PSTADE_operator(>=, false)

#undef  PSTADE_operator

} // infinity_detail


using infinity_detail::infinity;


} } // namespace pstade::oven


#endif
