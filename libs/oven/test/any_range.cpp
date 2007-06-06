#include "./prelude.hpp"
#include <pstade/vodka/drink.hpp>
#define PSTADE_CONCEPT_CHECK


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/any_range_fwd.hpp> // missing header check
#include <pstade/oven/any_range.hpp>


#include <string>
#include <boost/range.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/core.hpp>
#include <pstade/oven/identities.hpp>
#include <pstade/oven/filtered.hpp>
#include <pstade/oven/equals.hpp>


#include <pstade/unit_test.hpp>
#include "./detail/test.hpp"


void test_iterator()
{
    namespace oven = pstade::oven;
    using namespace oven;

    std::string src("abc");
    {
        any_iterator<char&, boost::forward_traversal_tag, char, std::ptrdiff_t> it1(boost::begin(src));
        std::string::iterator b = it1.base<std::string::iterator>();
        BOOST_CHECK( b == boost::begin(src) );
        any_iterator<char const&, boost::single_pass_traversal_tag, char, std::ptrdiff_t> it2 = it1; // copy-initialization.
        BOOST_CHECK( it2 == it1 );
        it2 = it1;
        BOOST_CHECK( it2 == it1 );
    }
    {
        any_iterator<char&, boost::random_access_traversal_tag, char, std::ptrdiff_t> it1(boost::begin(src));
        any_iterator<char const&, boost::random_access_traversal_tag, char, int> it2 = it1; // copy-initialization.
        BOOST_CHECK( it2 == it1 );
        BOOST_CHECK( (it2 - it1) == 0 );
        it2 = it1;
        BOOST_CHECK( it2 == it1 );
    }
    {
        any_iterator<char&, boost::forward_traversal_tag, char, std::ptrdiff_t> it1;
        it1 = boost::begin(src);
        std::string::iterator b = it1.base<std::string::iterator>();
        BOOST_CHECK( b == boost::begin(src) );
    }
    {
        any_iterator<char&, boost::single_pass_traversal_tag, char, std::ptrdiff_t> it1;
        it1 = boost::begin(src);
        std::string::iterator b = it1.base<std::string::iterator>();
        BOOST_CHECK( b == boost::begin(src) );
    }
}


void test_make()
{
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string str("abcdefg");
        boost::result_of<op_make_any_range(std::string&)>::type
            r = make_any_range(str);

        BOOST_CHECK( oven::equals(str, r) );
    }
}


void pstade_unit_test()
{
    ::test_iterator();

    namespace lambda = boost::lambda;
    namespace oven = pstade::oven;
    using namespace oven;

    {
        std::string a("8frj91j81hf891y2");
        any_range<char&, boost::random_access_traversal_tag> b(a);

        test::random_access_swappable(b, a);
        test::non_lightweight_copyable(b);
        BOOST_CHECK(b); // bool-testable check
    }
    {
        std::string a("8frj91j81hf891y2");
        any_range<char&, boost::random_access_traversal_tag> b; // DefaultConstructible
        b = a;
        test::random_access_swappable(b, a);
    }
    {
        std::string a("8frj91j81hf891y2");
        any_range<char&, boost::random_access_traversal_tag> b = a|identities; // copy-initializable with 'iter_range'.
        test::random_access_swappable(b, a);
    }
   {
        std::string a("8frj91j81hf891y2");
        any_range<char&, boost::random_access_traversal_tag> b = a|identities; // copy-initializable with 'iter_range'.
        any_range<char, boost::single_pass_traversal_tag> b2 = b; // copy-initializable with 'any_range'.
        test::single_pass_readable(b2, a);
    }
    {
        std::string a("8frj91j81hf891y2");
        any_range<char&, boost::bidirectional_traversal_tag> b(a|identities(boost::bidirectional_traversal_tag()));
        test::bidirectional_swappable(b, a);
    }
    {
        std::string a("8frj91j81hf891y2");
        any_range<char&, boost::forward_traversal_tag> b(a|identities(boost::forward_traversal_tag()));
        test::forward_swappable(b, a);
    }
    {
        std::string a("8frj91j81hf891y2");
        any_range<char&, boost::single_pass_traversal_tag> b(a|identities(boost::single_pass_traversal_tag()));
        test::single_pass_readable(b, a);
        test::lightweight_copyable(b);
    }
    {
        std::string a("8frj91j81hf891y2");
        any_range<char, boost::single_pass_traversal_tag> b = a|test::proxies;
        test::single_pass_readable(b, a);
        test::lightweight_copyable(b);
    }
    {
        std::string a;
        any_range<char&, boost::random_access_traversal_tag> b(a|identities);
        test::emptiness(b);
        BOOST_CHECK(!b); // bool-testable check
    }
    {
        std::string rng("abcd");
        typedef any_iterator<char&, boost::random_access_traversal_tag, char, std::ptrdiff_t> many_iter;
        many_iter many(boost::begin(rng));
        // many.base<char *>(); // bad_cast!
        many.base<std::string::iterator>();
    }
    {
        std::string str("jgi8e8qnboie");

        // rejected:
        // any_range_of<std::string>::type any_ = str; // copy-initializable
        
        any_range_of<std::string>::type any_(str); // copy-initializable
        BOOST_CHECK( equals(str, any_) );
    }

    ::test_make();
}
