#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/find_range.hpp>


#include <boost/algorithm/string.hpp>
#include <boost/range/sub_range.hpp>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <pstade/oven/equal.hpp>
#include <pstade/oven/null_terminate_range.hpp>
#include <pstade/oven/sequence_cast.hpp>


using namespace pstade;
using namespace oven;


struct fun
{
    explicit fun(std::vector<std::string>& out) :
        m_pout(&out)
        { }

    void operator()(boost::sub_range<std::string> m) const
    {
        m_pout->push_back(oven::sequence(m));
    }

    std::vector<std::string> *m_pout;
};


template< class Range, class Functor >
void for_each(const Range& rng, Functor f)
{
    std::for_each(boost::begin(rng), boost::end(rng), f);
}


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
            src|found( boost::algorithm::first_finder("abc"|null_terminated, boost::algorithm::is_iequal()) )
        ) {
            out.push_back(oven::sequence(m));
        }
#endif

        ::for_each(
            src|found( boost::first_finder("abc"|null_terminated, boost::is_iequal()) ),
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
