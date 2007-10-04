#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/checker.hpp>
#include <pstade/minimal_test.hpp>


#include <algorithm> // copy
#include <iterator>
#include <vector>
#include <pstade/oven/equals.hpp>
#include <pstade/oven/begin_end.hpp>
#include "./detail/output_iterator.hpp"



void pstade_minimal_test()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string const from("0123456789");
        std::vector<char> to(10);
        std::copy(boost::begin(from), boost::end(from), checker(to));
        BOOST_CHECK( equals(from, to) );

        to.clear();
        to.resize(10);
        std::copy(boost::begin(from), boost::end(from), checker(to, begin));
        BOOST_CHECK( equals(from, to) );
    }

    {
        std::string const from("0123456789");
        std::vector<char> to(7);

        bool thrown = false;
        try {
            std::copy(boost::begin(from), boost::end(from), checker(to));
        }
        catch (std::out_of_range const &) {
            thrown = true;
        }
        BOOST_CHECK(thrown);
    }
    {
        std::string const from("0123456789");
        std::vector<char> to(20);

        bool thrown = false;
        try {
            std::copy(boost::begin(from), boost::end(from), checker(to, end));
        }
        catch (std::out_of_range const &) {
            thrown = true;
        }
        BOOST_CHECK(thrown);
    }
    {
        std::vector<char> to(10);
        test::output_iterator(checker(to), 'a');
        test::output_iterator(checker(to, begin), 'a');
    }
}
