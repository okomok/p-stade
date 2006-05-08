#ifndef PSTADE_OVEN_CALL_HPP
#define PSTADE_OVEN_CALL_HPP


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/foreach.hpp>


#define PSTADE_OVEN_CALL0(Algo, Range) \
    PSTADE_OVEN_CALL_prelude(Range) \
    Algo(BOOST_FOREACH_BEGIN(Range).item, BOOST_FOREACH_END(Range).item) \
/**/


#define PSTADE_OVEN_CALL1(Algo, Range, A0) \
    PSTADE_OVEN_CALL_prelude(Range) \
    Algo(BOOST_FOREACH_BEGIN(Range).item, BOOST_FOREACH_END(Range).item, A0) \
/**/


#define PSTADE_OVEN_CALL2(Algo, Range, A0, A1) \
    PSTADE_OVEN_CALL_prelude(Range) \
    Algo(BOOST_FOREACH_BEGIN(Range).item, BOOST_FOREACH_END(Range).item, A0, A1) \
/**/


#define PSTADE_OVEN_CALL3(Algo, Range, A0, A1, A2) \
    PSTADE_OVEN_CALL_prelude(Range) \
    Algo(BOOST_FOREACH_BEGIN(Range).item, BOOST_FOREACH_END(Range).item, A0, A1, A2) \
/**/


#define PSTADE_OVEN_CALL_prelude(Range) \
    BOOST_FOREACH_PREAMBLE() \
    if (boost::foreach_detail_::auto_any_t _foreach_col = BOOST_FOREACH_CONTAIN(Range)) { } else \
/**/


#endif
