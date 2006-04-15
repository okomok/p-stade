#ifndef PSTADE_BISCUIT_PARSER_STAR_BEFORE_HPP
#define PSTADE_BISCUIT_PARSER_STAR_BEFORE_HPP


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "./before.hpp"
#include "./star_until.hpp"


namespace pstade { namespace biscuit {


template< class ParserA, class ParserB >
struct star_before :
	star_until< ParserA, before<ParserB> >
{ };


} } // namespace pstade::biscuit


#endif
