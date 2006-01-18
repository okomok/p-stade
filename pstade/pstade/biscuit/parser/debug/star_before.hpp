#pragma once

#include "./before.hpp"
#include "./star_until.hpp"

namespace pstade { namespace biscuit {


template< class ParserA, class ParserB >
struct star_before :
	star_until< ParserA, before<ParserB> >
{ };


} } // namespace pstade::biscuit
