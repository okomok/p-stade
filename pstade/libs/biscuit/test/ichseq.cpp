#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/algorithm/match.hpp>
#include <pstade/biscuit/parser/primitive/ichar.hpp>
#include <pstade/biscuit/parser/primitive/ichseq.hpp>
#include <pstade/biscuit/parser/seq.hpp>


#include <string>
#include <pstade/oven/as_literal.hpp>


void test()
{
    using namespace pstade;
    using namespace pstade::biscuit;

    // variadic forms
    //
    {
        std::string s0("aBc");
        BOOST_CHECK(( biscuit::match< seq< ichar<'a'>, ichar<'b'>, ichar<'c'> > >(s0) ));
        BOOST_CHECK(( biscuit::match< seq< ichar<'A'>, ichar<'B'>, ichar<'C'> > >(s0) ));
        BOOST_CHECK(( biscuit::match< seq< ichar<'A'>, ichar<'b'>, ichar<'C'> > >(s0) ));
        BOOST_CHECK(( biscuit::match< seq< ichar<'a'>, ichar<'B'>, ichar<'c'> > >(s0) ));

        BOOST_CHECK(( biscuit::match< ichseq<'a','b','c'> >(s0) ));
        BOOST_CHECK(( biscuit::match< ichseq<'A','B','C'> >(s0) ));
        BOOST_CHECK(( biscuit::match< ichseq<'A','b','C'> >(s0) ));
        BOOST_CHECK(( biscuit::match< ichseq<'a','B','c'> >(s0) ));
    }

    {
        const std::string s0("aBc");
        BOOST_CHECK(( biscuit::match< seq< ichar<'a'>, ichar<'b'>, ichar<'c'> > >(s0) ));
        BOOST_CHECK(( biscuit::match< seq< ichar<'A'>, ichar<'B'>, ichar<'C'> > >(s0) ));
        BOOST_CHECK(( biscuit::match< seq< ichar<'A'>, ichar<'b'>, ichar<'C'> > >(s0) ));
        BOOST_CHECK(( biscuit::match< seq< ichar<'a'>, ichar<'B'>, ichar<'c'> > >(s0) ));

        BOOST_CHECK(( biscuit::match< ichseq<'a','b','c'> >(s0) ));
        BOOST_CHECK(( biscuit::match< ichseq<'A','B','C'> >(s0) ));
        BOOST_CHECK(( biscuit::match< ichseq<'A','b','C'> >(s0) ));
        BOOST_CHECK(( biscuit::match< ichseq<'a','B','c'> >(s0) ));
    }

    {
        BOOST_CHECK(( biscuit::match< seq< ichar<'a'>, ichar<'b'>, ichar<'c'> > >("abc"|oven::as_literal) ));
        BOOST_CHECK(( biscuit::match< seq< ichar<'A'>, ichar<'B'>, ichar<'C'> > >("aBC"|oven::as_literal) ));
        BOOST_CHECK(( biscuit::match< seq< ichar<'A'>, ichar<'b'>, ichar<'C'> > >("Abc"|oven::as_literal) ));
        BOOST_CHECK(( biscuit::match< seq< ichar<'a'>, ichar<'B'>, ichar<'c'> > >("aBc"|oven::as_literal) ));

        BOOST_CHECK(( biscuit::match< ichseq<'a','b','c'> >("abc") ));
        BOOST_CHECK(( biscuit::match< ichseq<'A','B','C'> >("aBC") ));
        BOOST_CHECK(( biscuit::match< ichseq<'A','b','C'> >("Abc") ));
        BOOST_CHECK(( biscuit::match< ichseq<'a','B','c'> >("aBc") ));
    }


    // numbered forms
    //
    {
        std::string s0("aBc");
        BOOST_CHECK(( biscuit::match< seq3< ichar<'a'>, ichar<'b'>, ichar<'c'> > >(s0) ));
        BOOST_CHECK(( biscuit::match< seq3< ichar<'A'>, ichar<'B'>, ichar<'C'> > >(s0) ));
        BOOST_CHECK(( biscuit::match< seq3< ichar<'A'>, ichar<'b'>, ichar<'C'> > >(s0) ));
        BOOST_CHECK(( biscuit::match< seq3< ichar<'a'>, ichar<'B'>, ichar<'c'> > >(s0) ));

        BOOST_CHECK(( biscuit::match< ichseq3<'a','b','c'> >(s0) ));
        BOOST_CHECK(( biscuit::match< ichseq3<'A','B','C'> >(s0) ));
        BOOST_CHECK(( biscuit::match< ichseq3<'A','b','C'> >(s0) ));
        BOOST_CHECK(( biscuit::match< ichseq3<'a','B','c'> >(s0) ));
    }

    {
        const std::string s0("aBc");
        BOOST_CHECK(( biscuit::match< seq3< ichar<'a'>, ichar<'b'>, ichar<'c'> > >(s0) ));
        BOOST_CHECK(( biscuit::match< seq3< ichar<'A'>, ichar<'B'>, ichar<'C'> > >(s0) ));
        BOOST_CHECK(( biscuit::match< seq3< ichar<'A'>, ichar<'b'>, ichar<'C'> > >(s0) ));
        BOOST_CHECK(( biscuit::match< seq3< ichar<'a'>, ichar<'B'>, ichar<'c'> > >(s0) ));

        BOOST_CHECK(( biscuit::match< ichseq3<'a','b','c'> >(s0) ));
        BOOST_CHECK(( biscuit::match< ichseq3<'A','B','C'> >(s0) ));
        BOOST_CHECK(( biscuit::match< ichseq3<'A','b','C'> >(s0) ));
        BOOST_CHECK(( biscuit::match< ichseq3<'a','B','c'> >(s0) ));
    }

    {
        BOOST_CHECK(( biscuit::match< seq3< ichar<'a'>, ichar<'b'>, ichar<'c'> > >("abc"|oven::as_literal) ));
        BOOST_CHECK(( biscuit::match< seq3< ichar<'A'>, ichar<'B'>, ichar<'C'> > >("aBC"|oven::as_literal) ));
        BOOST_CHECK(( biscuit::match< seq3< ichar<'A'>, ichar<'b'>, ichar<'C'> > >("Abc"|oven::as_literal) ));
        BOOST_CHECK(( biscuit::match< seq3< ichar<'a'>, ichar<'B'>, ichar<'c'> > >("aBc"|oven::as_literal) ));

        BOOST_CHECK(( biscuit::match< ichseq3<'a','b','c'> >("abc"|oven::as_literal) ));
        BOOST_CHECK(( biscuit::match< ichseq3<'A','B','C'> >("aBC"|oven::as_literal) ));
        BOOST_CHECK(( biscuit::match< ichseq3<'A','b','C'> >("Abc"|oven::as_literal) ));
        BOOST_CHECK(( biscuit::match< ichseq3<'a','B','c'> >("aBc"|oven::as_literal) ));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
