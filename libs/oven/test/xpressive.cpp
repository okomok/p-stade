#include "./prelude.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/xpressive.hpp>
#include <pstade/minimal_test.hpp>
#include <boost/xpressive/sub_match.hpp>


#include <pstade/concept.hpp>
#include <pstade/oven/concepts.hpp>


namespace oven = pstade::oven;
using namespace oven;


PSTADE_CONCEPT_ASSERT((RandomAccess< boost::xpressive::sub_match<char *> >));


void pstade_minimal_test()
{

    {
    }
}
