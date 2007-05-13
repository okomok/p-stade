

// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include "stdafx.h"


#include <pstade/oven.hpp>
#include <pstade/require.hpp>


namespace biscuit = pstade::biscuit;
using namespace biscuit;


typedef chseq<
    'W','i','l','d',' ','i','s',' ','t','h','e',' ','w','i','n','d',' ','t','h','a','t',' ','s','t','r','i','p','s',' ','a','w','a','y',' ','o','u','r',' ','s','i','n','s'
> long_parser;


int main()
{
    PSTADE_REQUIRE( biscuit::match<long_parser>("Wild is the wind that strips away our sins"|pstade::oven::as_literal) );
    return 0;
}
