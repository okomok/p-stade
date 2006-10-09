#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/copy_range.hpp>


#include <iterator>
#include <sstream>
#include <string>
#include <vector>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/counting_range.hpp>
#include <pstade/oven/istream_range.hpp>


void test()
{
    namespace oven = pstade::oven;
    using namespace oven;

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

#if 0 // rejected
    {
        std::string   in("hello, copied!");
        std::string out1("hello, ranges!");
        std::string out2("hello, ranges!");
        std::string out3("hello, ranges!");
        in|copied_out(out1);
        in|copied_out(out2)|copied_out(out3);
        BOOST_CHECK( oven::equals(in, out1) );
        BOOST_CHECK( oven::equals(in, out2) );
        BOOST_CHECK( oven::equals(in, out3) );
    }
#endif

    {
        std::string   in("hello, copied!");
        std::string out1;
        std::string out2;
        std::string out3;
        in|copied_out(std::back_inserter(out1));
        in|copied_out(std::back_inserter(out2))|copied_out(std::back_inserter(out3));
        BOOST_CHECK( oven::equals(in, out1) );
        BOOST_CHECK( oven::equals(in, out2) );
        BOOST_CHECK( oven::equals(in, out3) );
    }

    {
        std::string in("hello, copied_out!");
        std::string out = in|copied;
        BOOST_CHECK( oven::equals(in, out) );
    }

#if 0 // rejected
    {
        std::stringstream ss;
        std::string ans("abcdefg");
        ss << ans;

        std::vector<char> out = ans|copied;
        oven::make_istream_range<char>(ss)|copied_out(out);
        BOOST_CHECK( oven::equals(out, ans) );
    }
#endif

#if 0 // illegal
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


// extension test
//

#include <pstade/oven/extension.hpp>


namespace xxx {

    struct X{ };

}

namespace pstade_oven_extension {

    template< >
    struct Range< xxx::X >
    {
        template< class X, class From >
        X copy(From& rng)
        {
            (void)rng;
            return xxx::X();
        }
    };

}


void test_extension()
{
    using namespace pstade;
    using namespace oven;

    xxx::X x = std::string()|copied;
    (void)x;
}


int test_main(int, char*[])
{
    ::test();
    ::test_extension();
    return 0;
}
