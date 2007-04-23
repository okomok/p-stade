#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser.hpp>
#include <pstade/biscuit/algorithm/match.hpp>


#include <string>
#include <pstade/biscuit/alias.hpp>


using namespace biscuit;


void test()
{
    {
        std::string text("xxx");
        typedef longest3< chseq1<'x'>, chseq3<'x','x','x'>, chseq2<'x','x'> > longp;
        BOOST_CHECK(( biscuit::match< longp >(text) ));
    }

    {
        const std::string text("xxx");
        typedef shortest3< chseq1<'x'>, chseq3<'x','x','x'>, chseq2<'x','x'> > shortp;
        BOOST_CHECK(( biscuit::match< seq2< shortp, chseq2<'x','x'> > >(text) ));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
