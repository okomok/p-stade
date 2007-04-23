#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/algorithm/match.hpp>
#include <pstade/biscuit/parser.hpp>


#include <string>
#include <vector>
#include <pstade/biscuit/alias.hpp>


using namespace biscuit;


void test()
{
    std::vector<std::string> dictionary;
    dictionary.push_back("hello");
    dictionary.push_back("cute");
    dictionary.push_back("rngseq");

    BOOST_CHECK((
        biscuit::match< seq< rngseq<>, chseq<'!'> > >(std::string("hellocuterngseq!"), dictionary)
    ));

    BOOST_CHECK((
        biscuit::match< seq< chseq<'*'>, rngseq<biscuit::identity_fun>, chseq<'*'> > >(std::string("*hellocuterngseq*"), dictionary)
    ));

    BOOST_CHECK((
        biscuit::match< seq< rngseq<>, chseq<'!'> > >(std::string("hellocuterngseq!"), dictionary)
    ));
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
