#ifndef PSTADE_BISCUIT_PARSER_DIRECTIVE_SHORTESTN_HPP
#define PSTADE_BISCUIT_PARSER_DIRECTIVE_SHORTESTN_HPP


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/boost_workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    #pragma warning(push)
    #pragma warning(disable:4663)
#endif


#include <iterator> // distance
#include <limits> // numeric_limits
#include <boost/iterator/iterator_traits.hpp> // iterator_difference
#include <boost/mpl/void.hpp>
#include <pstade/oven/range_iterator.hpp>
#include "../../state/advance.hpp"


#if defined(PSTADE_BISCUIT_CFG_NO_PREPROCESSED_HEADERS)
    #include "../../detail/preprocessing/shortestn.hpp"
#else
    #include "../../detail/preprocessed/shortestn.hpp"
#endif


#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    #pragma warning(pop)
#endif


#endif
