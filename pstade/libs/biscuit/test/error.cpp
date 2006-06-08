#include <pstade/vodka/drink.hpp>
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
#include <boost/algorithm/string.hpp>
#include <boost/range.hpp>
#include <pstade/oven.hpp>


using namespace pstade;
using namespace biscuit;


struct handler
{
    template< class State, class UserState >
    error_status operator()(State&, UserState&, boost::sub_range<std::string> rng, int id)
    {
        BOOST_CHECK(( id == 3 ));
        boost::to_lower(rng);
        return error_retry;
    }
};


void test()
{
    {
        typedef guard<
            seq< chseq<'a','b','c'>, expect< 3, chseq<'d'> > >,
            handler
        > start;

        std::string s("abcD");
        BOOST_CHECK( biscuit::match<start>(s) );
        BOOST_CHECK( oven::equal(s, "abcd") );
    }
}


int test_main(int, char*[])
{
    ::test();

    return 0;
}
