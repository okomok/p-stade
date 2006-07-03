#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/construct.hpp>
#include <pstade/oven/sequence_cast.hpp>


#include <string>
#include <vector>
#include <pstade/oven/algorithms.hpp>
#include <pstade/oven/counting_range.hpp>


void test()
{
    using namespace pstade;
    using namespace oven;

    {
        std::string str("abcdefg");
        std::vector<char> vec = oven::sequence_cast< std::vector<char> >(str);
        BOOST_CHECK( oven::equals(vec, str) );
    }

    {
        std::string str("abcdefg");
        std::vector<char> vec = oven::sequence(str);
        BOOST_CHECK( oven::equals(vec, str) );
    }

    {
        std::vector<int> vec = oven::construct(oven::make_counting_range(3, 9));
        vec.push_back(9);
        BOOST_CHECK( oven::equals(vec, oven::make_counting_range(3, 10)) );
    }

    {
        std::string str("abcdefg");
        std::vector<char> vec = oven::constructor< std::vector<char> >(str);
        BOOST_CHECK( oven::equals(vec, str) );
    }

    {
        std::string str("abcdefg");
        std::vector<char> vec = oven::construct(str);
        BOOST_CHECK( oven::equals(vec, str) );
    }
}


// customization test
//

namespace xxx {

    struct X{ };

}

template< class Range > inline
xxx::X pstade_oven_construct(Range& rng, pstade::overload<xxx::X>)
{
    return xxx::X();
}

namespace yyy {

    struct Y { };

    template< class Range > inline
    Y pstade_oven_construct(Range& rng, pstade::overload<Y>)
    {
        return Y();
    }

}

void test_customization()
{
    using namespace pstade;
    using namespace oven;

    xxx::X x = oven::construct(std::string());
    yyy::Y y = oven::construct(std::string());
}


int test_main(int, char*[])
{
    ::test();
    ::test_customization();
    return 0;
}
