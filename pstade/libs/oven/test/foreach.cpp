#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/foreach.hpp>


#include <string>
#include <vector>
#include <boost/noncopyable.hpp>
#include <pstade/oven/identities.hpp>


namespace oven = pstade::oven;
using namespace oven;


std::string str("abcdefg");


void test_type()
{
    std::string out;
    PSTADE_OVEN_FOREACH (it, str|identities|identities)
        out.push_back(*it);

    BOOST_CHECK( str == out );
}


template<class Range>
void test_template(Range& rng)
{
    std::string out;
    PSTADE_OVEN_FOREACH_TPL (it, rng|identities|identities) {
        out.push_back(*it);
    }

    BOOST_CHECK( str == out );
}


void test_empty()
{
    std::string str;
    PSTADE_OVEN_FOREACH (it, str|identities|identities) {
        BOOST_CHECK(false);
    }
    BOOST_CHECK( str.empty() );
}


// call once check
int counter = 0;
std::vector<int> my_vector(4,4);
std::vector<int> const &get_vector()
{
    ++counter;
    return my_vector;
}

void test_call_once()
{
    PSTADE_OVEN_FOREACH (it, ::get_vector()) {
        ((void)it); // no-op
    }
    BOOST_CHECK(1 == counter);
}


// no copying check
struct noncpyvec : std::vector<int>, boost::noncopyable
{ };

void test_no_copying()
{
    ::noncpyvec v;
    PSTADE_OVEN_FOREACH (it, v) {
        (void)it;
    }
}

#if !defined(BOOST_FOREACH_NO_CONST_RVALUE_DETECTION)
    std::vector<int> const get_rvalue_vector()
    {
        return std::vector<int>(4, 4);
    }
    void test_nonlightweight_rvalue()
    {
        int counter = 0;

        PSTADE_OVEN_FOREACH (i, get_rvalue_vector())
        {
            counter += *i;
        }

        BOOST_CHECK(16 == counter);
    }
#endif

int test_main(int, char*[])
{
    ::test_type();
    ::test_template(str);
    ::test_empty();
    ::test_call_once();
    ::test_no_copying();
    ::test_nonlightweight_rvalue();
    return 0;
}
