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
#include <pstade/const.hpp>
#include <pstade/oven/null_terminate_range.hpp>


using namespace pstade;
using namespace biscuit;


struct xml_comment :
    seq3<
        chseq4<'<','!','-','-'>,
        star<
            or_2<
                minus2< any, chseq1<'-'> >,
                seq2<
                    chseq1<'-'>,
                    minus2< any, chseq1<'-'> >
                >
            >
        >,
        chseq3<'-','-','>'>
    >
{ };


void test()
{
    {
        typedef seq2<
            chseq2<'/','*'>,
            star_until< any, chseq2<'*','/'> >
        > c_comment;

        BOOST_CHECK( biscuit::match<c_comment>("/* hello, c comment */"|oven::null_terminated) );
    }
    
    {
        BOOST_CHECK( biscuit::match<xml_comment>("<!-- hello, xml comment -->"|oven::null_terminated) );
        BOOST_CHECK( !biscuit::match<xml_comment>("<!-- not well-formed comment -- -->"|oven::null_terminated) );
    }
    {
        std::string str("<!-- hello, xml comment -->");
        BOOST_CHECK( biscuit::match<xml_comment>(str) );
    }
    {
        const std::string str("<!-- hello, xml comment -->");
        BOOST_CHECK( biscuit::match<xml_comment>(str) );
    }
    {
        std::string str("<!-- hello, xml comment -->");
        BOOST_CHECK( biscuit::match<xml_comment>(pstade::const_(str)) );
    }

    {
        int text[] = { 1, 2, 3 };
        BOOST_CHECK(( biscuit::match< bchseq3<int, 1, 2, 3> >(text) ));
    }

    {
        const int text[] = { 1, 2, 3 };
        BOOST_CHECK(( biscuit::match< bchseq3<int, 1, 2, 3> >(text) ));
    }

    {
        std::string str; // empty
        BOOST_CHECK( biscuit::match<eps>(str) );
        BOOST_CHECK( !biscuit::match<any>(str) );
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
