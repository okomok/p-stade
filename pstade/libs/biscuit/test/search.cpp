#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/algorithm/search.hpp>
#include <pstade/biscuit/parser.hpp>


#include <string>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>


using namespace pstade;
using namespace biscuit;


struct c_comment :
    seq2<
        chseq2<'/','*'>,
        star_until< any, chseq2<'*','/'> >
    >
{ };


void test()
{
    {
        std::string text("  int i; /* c comment */ int j; ");
        boost::sub_range<std::string> rng = biscuit::search<c_comment>(text);
        BOOST_CHECK(oven::equal(rng, "/* c comment */") );
    }

    {
        const std::string text("// not c comment, but c++ comment ");
        boost::sub_range<const std::string> rng = biscuit::search<c_comment>(text);
        BOOST_CHECK( boost::empty(rng) );
    }

    {
        int text[4] = { 1, 2, 3, 4 };
        boost::sub_range<int [4]> rng = biscuit::search< bchseq2<int, 2, 3> >(text);
        BOOST_CHECK( oven::equal(rng, "\2\3") );
    }

    {
        const int text[4] = { 1, 2, 3, 4 };
        boost::sub_range<const int [4]> rng = biscuit::search< bchseq2<int, 2, 3> >(text);
        BOOST_CHECK( oven::equal(rng, "\2\3") );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
