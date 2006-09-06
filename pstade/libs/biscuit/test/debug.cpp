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
#include <pstade/biscuit/algorithm/parse.hpp>


#include <string>
#include <pstade/oven.hpp>


using namespace pstade;
using namespace biscuit;


void test()
{
    {
        std::string src("hello, debug!");
        std::string out;

        biscuit::debugger_reset_ostream(out);

        BOOST_CHECK((
            biscuit::match<
                seq<
                    debugger< int, repeat<any, 7> >,
                    chseq<'d','e','b','u','g','!'>
                >
            >(src)
        ));

        BOOST_CHECK( !out.empty() );
        std::cout << out << std::endl;
    }

#if !defined(PSTADE_NAPKIN_NO_WIDESTRING)
    {
        std::wstring wsrc(L"hello, debug!");
        std::wstring wout;

        biscuit::wdebugger_reset_ostream(wout);

        BOOST_CHECK((
            biscuit::match<
                seq<
                    wdebugger< double, repeat<any, 7> >,
                    chseq<'d','e','b','u','g','!'>
                >
            >(wsrc)
        ));

        BOOST_CHECK( !wout.empty() );
        std::wcout << wout << std::endl;
    }
#endif

    {
        std::string src("hello, debug!");
        std::string out;

        biscuit::debugger_reset_ostream(out);

        BOOST_CHECK((
            biscuit::match<
                seq<
                    debugger< int, repeat<any, 7>, boost::mpl::false_ >,
                    chseq<'d','e','b','u','g','!'>
                >
            >(src)
        ));

        BOOST_CHECK( out.empty() );
    }
}


int test_main(int, char*[])
{
    ::test();

    return 0;
}
