#ifndef PSTADE_BISCUIT_PARSER_MINUSN_HPP
#define PSTADE_BISCUIT_PARSER_MINUSN_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


// Note:
//   For VC7.1, Set of small if-statement seems faster than one big if-statement.


#include <boost/mpl/void.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/result_iterator.hpp>
#include "../state/cur_guard.hpp"
#include "../state/match.hpp"


#if defined(PSTADE_BISCUIT_CFG_NO_PREPROCESSED_HEADERS)
    #include "../detail/preprocessing/minusn.hpp"
#else
    #include "../detail/preprocessed/minusn.hpp"
#endif


#endif
