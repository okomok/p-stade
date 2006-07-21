#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/sequence_cast.hpp>


#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/counting_range.hpp>
#include <pstade/oven/istream_range.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        std::string rng("abcdefg");
        std::vector<char> vec = oven::sequence_cast< std::vector<char> >(rng);
        BOOST_CHECK( oven::equals(vec, rng) );
    }

    {
        std::string rng("abcdefg");
        std::vector<char> vec = oven::sequence(rng);
        BOOST_CHECK( oven::equals(vec, rng) );
    }

    {
        std::vector<int> vec = oven::make_counting_range(3, 9)|copied;
        vec.push_back(9);
        BOOST_CHECK( oven::equals(vec, oven::make_counting_range(3, 10)) );
    }

    {
        std::string rng("abcdefg");
        std::vector<char> vec = oven::copy_range< std::vector<char> >(rng);
        BOOST_CHECK( oven::equals(vec, rng) );
    }

    {
        std::string rng("abcdefg");
        std::vector<char> vec = rng|copied;
        BOOST_CHECK( oven::equals(vec, rng) );
    }

    {
        std::string   in("hello, copied!");
        std::string out1("hello, ranges!");
        std::string out2("hello, ranges!");
        std::string out3("hello, ranges!");
        in|copied(out1);
        in|copied(out2)|copied(out3);
        BOOST_CHECK( oven::equals(in, out1) );
        BOOST_CHECK( oven::equals(in, out2) );
        BOOST_CHECK( oven::equals(in, out3) );
    }

    {
        std::string   in("hello, copied!");
        std::string out1;
        std::string out2;
        std::string out3;
        in|copied(std::back_inserter(out1));
        in|copied(std::back_inserter(out2))|copied(std::back_inserter(out3));
        BOOST_CHECK( oven::equals(in, out1) );
        BOOST_CHECK( oven::equals(in, out2) );
        BOOST_CHECK( oven::equals(in, out3) );
    }

    {
        std::string in("hello, copied!");
        std::string out = in|copied;
        BOOST_CHECK( oven::equals(in, out) );
    }

    {
        std::stringstream ss;
        std::string ans("abcdefg");
        ss << ans;

        std::vector<char> out = ans|copied;
        oven::make_istream_range<char>(ss)|copied(out);
        BOOST_CHECK( oven::equals(out, ans) );
    }

#if 0
    {
        std::string rng("abcdefg");
        std::vector<char> vec(rng|copied);
        BOOST_CHECK( oven::equals(vec, rng) );
    }
#endif
}


inline
std::vector<char> fun()
{
    using namespace pstade;
    using namespace oven;
    return oven::make_counting_range(3, 10)|copied;
}


// customization test
//

namespace xxx {

    struct X{ };

}

template< class Range > inline
xxx::X pstade_oven_copy_range(Range& rng, pstade::overload<xxx::X>)
{
    (void)rng;
    return xxx::X();
}

namespace yyy {

    struct Y { };

    template< class Range > inline
    Y pstade_oven_copy_range(Range& rng, pstade::overload<Y>)
    {
        (void)rng;
        return Y();
    }

}

void test_customization()
{
    using namespace pstade;
    using namespace oven;

    xxx::X x = std::string()|copied;
    (void)x;
    yyy::Y y = std::string()|copied;
    (void)y;
}


int test_main(int, char*[])
{
    ::test();
    ::test_customization();
    return 0;
}
