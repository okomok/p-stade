#include "./prefix.hpp"


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2007.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/with_line_number.hpp>
#include <pstade/minimal_test.hpp>
#include "./detail/test.hpp"


#include <string>
#include <iterator> // advance
#include <pstade/oven/identities.hpp>


namespace oven = pstade::oven;
using namespace oven;


template<class Rng>
void check_line_number(Rng& rng, int adv, int ans)
{
    typedef typename range_iterator<Rng>::type iter_t;

    iter_t first = boost::begin(rng);
    iter_t first_ = first;
    std::advance(first, adv);
    BOOST_CHECK(oven::line_number<int>(first) == ans);

    std::advance(first_, adv);
    BOOST_CHECK(oven::line_number<int>(first_) == ans);
}


void pstade_minimal_test()
{
    {
        std::string a("abc\nef\ng\nh\ngkln\nopq\n\n");
        std::string b("abc\nef\ng\nh\ngkln\nopq\n\n");
        ::check_line_number(b|with_line_number(0), 12, 4);
        test::forward_swappable(b|with_line_number(0), a);
    }
    {
        std::string a("abc\nef\ng\nh\ngkln\nopq\n\n");
        std::string b("abc\nef\ng\nh\ngkln\nopq\n\n");
        ::check_line_number(b|with_line_number(3), 12, 7);
        test::forward_swappable(b|with_line_number(3), a);
    }
    {
        std::string a("abcNefNgNhNgklnNopqNN");
        std::string b("abcNefNgNhNgklnNopqNN");
        ::check_line_number(b|with_line_number(0, 'N'), 12, 4);
        test::forward_swappable(b|with_line_number(0, 'N'), a);
    }
    {
        int a[] = { 1,2,3,9,3,2,9,5,9,8,9,4,2,0,7,9,2,2,2,9,9 };
        int b[] = { 1,2,3,9,3,2,9,5,9,8,9,4,2,0,7,9,2,2,2,9,9 };
        ::check_line_number(b|with_line_number(0, 9), 12, 4);
        test::forward_swappable(b|with_line_number(0, 9), a);
    }
    {
        test::emptiness(
            std::string()|with_line_number(0)
        );
    }
    {
        std::string b("abc\nef\ng\nh\ngkln\nopq\n\n");
        ::check_line_number(b|with_line_number(0), 12, 4);
        ::check_line_number(b|with_line_number(0)|identities|identities, 12, 4);
    }
}
