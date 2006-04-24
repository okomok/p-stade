#include <pstade/vodka/begin.hpp>
#include <boost/test/minimal.hpp>


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/parser.hpp>
#include <pstade/biscuit/algorithm/match.hpp>


#include <string>
#include <vector>
#include <pstade/oven/copy.hpp>
#include <pstade/oven/null_terminate_range.hpp>


void test()
{
    using namespace pstade;
    using namespace biscuit;

    // variadic forms
    {
        std::vector<char> text; {
            oven::copy("aBcDefgH"|oven::null_terminated, std::back_inserter(text));
        }
        BOOST_CHECK((  biscuit::match< seq< as_lower< chseq<'a','b','c','d','e'> >, chseq<'f','g','H'> > >(text) ));
        BOOST_CHECK(( !biscuit::match< seq< as_lower< chseq<'a','b','c','d','e'> >, chseq<'F','g','H'> > >(text) ));
        BOOST_CHECK(( !biscuit::match< seq< as_lower< chseq<'a','b','C','d','e'> >, chseq<'f','g','H'> > >(text) ));
        BOOST_CHECK(( !biscuit::match< seq< as_lower< chseq<'a','b','c','d','E'> >, chseq<'F','g','H'> > >(text) ));
    }

    {
        const std::string text("aBcDefgH");
        BOOST_CHECK((  biscuit::match< seq< as_lower< chseq<'a','b','c','d','e'> >, chseq<'f','g','H'> > >(text) ));
        BOOST_CHECK(( !biscuit::match< seq< as_lower< chseq<'a','b','c','d','e'> >, chseq<'F','g','H'> > >(text) ));
        BOOST_CHECK(( !biscuit::match< seq< as_lower< chseq<'a','b','C','d','e'> >, chseq<'f','g','H'> > >(text) ));
        BOOST_CHECK(( !biscuit::match< seq< as_lower< chseq<'a','b','c','d','E'> >, chseq<'F','g','H'> > >(text) ));
    }

    {
        BOOST_CHECK((  biscuit::match< seq< as_lower< chseq<'a','b','c','d','e'> >, chseq<'f','g','H'> > >("aBcDefgH"|oven::null_terminated) ));
        BOOST_CHECK(( !biscuit::match< seq< as_lower< chseq<'a','b','c','d','e'> >, chseq<'F','g','H'> > >("aBcDefgH"|oven::null_terminated) ));
        BOOST_CHECK(( !biscuit::match< seq< as_lower< chseq<'a','b','C','d','e'> >, chseq<'f','g','H'> > >("aBcDefgH"|oven::null_terminated) ));
        BOOST_CHECK(( !biscuit::match< seq< as_lower< chseq<'a','b','c','d','E'> >, chseq<'F','g','H'> > >("aBcDefgH"|oven::null_terminated) ));
    }

    // numbered forms
    {
        std::string text("aBcDefgH");
        BOOST_CHECK((  biscuit::match< seq2< as_lower< chseq5<'a','b','c','d','e'> >, chseq3<'f','g','H'> > >(text) ));
        BOOST_CHECK(( !biscuit::match< seq2< as_lower< chseq5<'a','b','c','d','e'> >, chseq3<'F','g','H'> > >(text) ));
        BOOST_CHECK(( !biscuit::match< seq2< as_lower< chseq5<'a','b','C','d','e'> >, chseq3<'f','g','H'> > >(text) ));
        BOOST_CHECK(( !biscuit::match< seq2< as_lower< chseq5<'a','b','c','d','E'> >, chseq3<'F','g','H'> > >(text) ));
    }

    {
        const std::string text("aBcDefgH");
        BOOST_CHECK((  biscuit::match< seq2< as_lower< chseq5<'a','b','c','d','e'> >, chseq3<'f','g','H'> > >(text) ));
        BOOST_CHECK(( !biscuit::match< seq2< as_lower< chseq5<'a','b','c','d','e'> >, chseq3<'F','g','H'> > >(text) ));
        BOOST_CHECK(( !biscuit::match< seq2< as_lower< chseq5<'a','b','C','d','e'> >, chseq3<'f','g','H'> > >(text) ));
        BOOST_CHECK(( !biscuit::match< seq2< as_lower< chseq5<'a','b','c','d','E'> >, chseq3<'F','g','H'> > >(text) ));
    }

    {
        BOOST_CHECK((  biscuit::match< seq2< as_lower< chseq5<'a','b','c','d','e'> >, chseq3<'f','g','H'> > >("aBcDefgH"|oven::null_terminated) ));
        BOOST_CHECK(( !biscuit::match< seq2< as_lower< chseq5<'a','b','c','d','e'> >, chseq3<'F','g','H'> > >("aBcDefgH"|oven::null_terminated) ));
        BOOST_CHECK(( !biscuit::match< seq2< as_lower< chseq5<'a','b','C','d','e'> >, chseq3<'f','g','H'> > >("aBcDefgH"|oven::null_terminated) ));
        BOOST_CHECK(( !biscuit::match< seq2< as_lower< chseq5<'a','b','c','d','E'> >, chseq3<'F','g','H'> > >("aBcDefgH"|oven::null_terminated) ));
    }
}


int test_main(int, char*[])
{
    ::test();

    return 0;
}
