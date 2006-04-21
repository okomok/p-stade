#ifndef PSTADE_BISCUIT_PARSER_MAX_REPEAT_HPP
#define PSTADE_BISCUIT_PARSER_MAX_REPEAT_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./repeat.hpp"


namespace pstade { namespace biscuit {


template< class Parser, unsigned int max >
struct max_repeat :
    repeat<Parser, 0, max>
{ };


} } // namespace pstade::biscuit


#endif
