#ifndef PSTADE_OVEN_CALL_HPP
#define PSTADE_OVEN_CALL_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/foreach.hpp>
#include <boost/mpl/aux_/preprocessor/is_seq.hpp>
#include <boost/mpl/aux_/preprocessor/token_equal.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/debug/assert.hpp>
#include <boost/preprocessor/seq/enum.hpp>


#define PSTADE_OVEN_CALL(Algo, Range, EmptyOrArgSeq) \
    BOOST_PP_ASSERT(PSTADE_OVEN_CALL_valid(EmptyOrArgSeq)) \
    \
    PSTADE_OVEN_CALL_prelude(Range) \
    \
    BOOST_PP_IIF (BOOST_MPL_PP_IS_SEQ(EmptyOrArgSeq), \
        PSTADE_OVEN_CALL_args, \
        PSTADE_OVEN_CALL_no_args \
    )(Algo, Range, EmptyOrArgSeq) \
/**/


#define PSTADE_OVEN_CALL_valid(EmptyOrArgSeq) \
    BOOST_PP_IIF (BOOST_MPL_PP_IS_SEQ(EmptyOrArgSeq), \
        1 BOOST_PP_TUPLE_EAT(2), \
        BOOST_MPL_PP_TOKEN_EQUAL \
    )(EmptyOrArgSeq, empty) \
/**/


#define BOOST_MPL_PP_TOKEN_EQUAL_empty(A) \
    A \
/**/


#define PSTADE_OVEN_CALL_no_args(Algo, Range, Unused) \
    Algo(BOOST_FOREACH_BEGIN(Range).item, BOOST_FOREACH_END(Range).item) \
/**/


#define PSTADE_OVEN_CALL_args(Algo, Range, ArgSeq) \
    Algo(BOOST_FOREACH_BEGIN(Range).item, BOOST_FOREACH_END(Range).item, BOOST_PP_SEQ_ENUM(ArgSeq)) \
/**/


#define PSTADE_OVEN_CALL_prelude(Range) \
    BOOST_FOREACH_PREAMBLE() \
    if (boost::foreach_detail_::auto_any_t _foreach_col = BOOST_FOREACH_CONTAIN(Range)) { } else \
/**/


#endif
