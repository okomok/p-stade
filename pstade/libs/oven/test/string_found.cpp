#include "./prefix.hpp"
#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/detail/boost_begin_end.hpp>


#include "./detail/v1_tests.hpp"
#include <pstade/oven/string_found.hpp>


#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/range/sub_range.hpp>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <pstade/oven/algorithm.hpp>
#include "./detail/v1_core.hpp"
#include <pstade/oven/as_literal.hpp>
#include <pstade/oven/copied.hpp>


namespace oven = pstade::oven;
using namespace oven;


struct fun
{
    explicit fun(std::vector<std::string>& out) :
        m_pout(&out)
        { }

    void operator()(boost::sub_range<std::string> m) const
    {
        m_pout->push_back(m|oven::copied);
    }

    std::vector<std::string> *m_pout;
};


void test()
{
    std::string src("abc-*-ABC-*-aBc");

    std::vector<std::string> ans; {
        ans.push_back("abc");
        ans.push_back("ABC");
        ans.push_back("aBc");
    }

    {
        std::vector<std::string> out;
#if 0
        // ICE under VC7.1/8.
        BOOST_FOREACH (
            boost::sub_range<std::string> m,
            src|string_found( boost::algorithm::first_finder("abc"|as_literal, boost::algorithm::is_iequal()) )
        ) {
            out.push_back(m|oven::copied);
        }
#endif

        oven::for_each(
            src|string_found( boost::first_finder("abc"|as_literal, boost::is_iequal()) ),
            ::fun(out)
        );

        BOOST_CHECK(( oven::equals(out, ans) ));
    }

}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
