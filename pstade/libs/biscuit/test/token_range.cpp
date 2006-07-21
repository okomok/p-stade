#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#define PSTADE_BISCUIT_CFG_NULLARY_CLASS_TEMPLATE_PARSER
#include <pstade/biscuit/parser.hpp>
#include <pstade/biscuit/range/token_range.hpp>


#include <string>
#include <boost/foreach.hpp>
#include <boost/range.hpp>
#include <boost/range/concepts.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/null_terminate_range.hpp>


using namespace pstade;
using namespace pstade::biscuit;


struct c_comment :
    seq<
        chseq<'/','*'>,
        star_until< any<>, chseq<'*','/'> >
    >
{ };


struct c_comment_n :
    seq2<
        chseq2<'/','*'>,
        star_until< any<>, chseq2<'*','/'> >
    >
{ };


#define SRC_TEXT \
    "char c; /* c comment no.1 */int i;/* c comment no.2 */i = 1;/* c comment no.3 */ ++i;  " \
/**/


void test()
{
#if 1
    std::string ans0("/* c comment no.1 */");
    std::string ans1("/* c comment no.2 */");
    std::string ans2("/* c comment no.3 */");

    // concept check
    //
    {
        typedef token_range<c_comment, std::string> rng_t;
        boost::function_requires< boost::ForwardRangeConcept<rng_t> >();
    }

    // variadic forms
    //
    {
        std::string src(SRC_TEXT);
        int i = 0;
        token_range<c_comment, std::string> ans(src);
        BOOST_FOREACH (boost::sub_range<std::string> rng, ans) {
            if (i == 0)
                BOOST_CHECK( oven::equals(rng, ans0) );
            if (i == 1)
                BOOST_CHECK( oven::equals(rng, ans1) );
            if (i == 2)
                BOOST_CHECK( oven::equals(rng, ans2) );
            ++i;
        }
        BOOST_CHECK(i == 3);
    }

    {
        const std::string src(SRC_TEXT);
        int i = 0;
        token_range<c_comment, const std::string> ans(src);
        BOOST_FOREACH (boost::sub_range<const std::string> rng, ans) {
            if (i == 0)
                BOOST_CHECK( oven::equals(rng, ans0) );
            if (i == 1)
                BOOST_CHECK( oven::equals(rng, ans1) );
            if (i == 2)
                BOOST_CHECK( oven::equals(rng, ans2) );
            ++i;
        }
        BOOST_CHECK(i == 3);
    }

    {
        int i = 0;
        BOOST_FOREACH (
            boost::sub_range<const char *> rng,
            make_token_range<c_comment>(SRC_TEXT|oven::null_terminated))
        {
            if (i == 0)
                BOOST_CHECK( oven::equals(rng, ans0) );
            if (i == 1)
                BOOST_CHECK( oven::equals(rng, ans1) );
            if (i == 2)
                BOOST_CHECK( oven::equals(rng, ans2) );
            ++i;
        }
        BOOST_CHECK(i == 3);
    }

    {
        int i = 0;
        BOOST_FOREACH (
            boost::sub_range<const char *> rng,
            SRC_TEXT |
                oven::null_terminated |
                tokenized<c_comment>()
        )
        {
            if (i == 0)
                BOOST_CHECK( oven::equals(rng, ans0) );
            if (i == 1)
                BOOST_CHECK( oven::equals(rng, ans1) );
            if (i == 2)
                BOOST_CHECK( oven::equals(rng, ans2) );
            ++i;
        }
        BOOST_CHECK(i == 3);
    }


    // numbered forms
    //
    {
        std::string src(SRC_TEXT);
        int i = 0;
        token_range<c_comment_n, std::string> ans(src);
        BOOST_FOREACH (boost::sub_range<std::string> rng, ans) {
            if (i == 0)
                BOOST_CHECK( oven::equals(rng, ans0) );
            if (i == 1)
                BOOST_CHECK( oven::equals(rng, ans1) );
            if (i == 2)
                BOOST_CHECK( oven::equals(rng, ans2) );
            ++i;
        }
        BOOST_CHECK(i == 3);
    }

    {
        const std::string src(SRC_TEXT);
        int i = 0;
        token_range<c_comment_n, const std::string> ans(src);
        BOOST_FOREACH (boost::sub_range<const std::string> rng, ans) {
            if (i == 0)
                BOOST_CHECK( oven::equals(rng, ans0) );
            if (i == 1)
                BOOST_CHECK( oven::equals(rng, ans1) );
            if (i == 2)
                BOOST_CHECK( oven::equals(rng, ans2) );
            ++i;
        }
        BOOST_CHECK(i == 3);
    }

    {
        int i = 0;
        BOOST_FOREACH (
            boost::sub_range<const char *> rng,
            biscuit::make_token_range<c_comment_n>(SRC_TEXT|oven::null_terminated))
        {
            if (i == 0)
                BOOST_CHECK( oven::equals(rng, ans0) );
            if (i == 1)
                BOOST_CHECK( oven::equals(rng, ans1) );
            if (i == 2)
                BOOST_CHECK( oven::equals(rng, ans2) );
            ++i;
        }
        BOOST_CHECK(i == 3);
    }

    {
        int i = 0;
        BOOST_FOREACH (
            boost::sub_range<const char *> rng,
            SRC_TEXT |
                oven::null_terminated |
                biscuit::tokenized<c_comment_n>()
        )
        {
            if (i == 0)
                BOOST_CHECK(oven::equals(rng, ans0));
            if (i == 1)
                BOOST_CHECK(oven::equals(rng, ans1));
            if (i == 2)
                BOOST_CHECK(oven::equals(rng, ans2));
            ++i;
        }
        BOOST_CHECK(i == 3);
    }

    {
        using namespace biscuit;

        std::string text("\r\nxyz\nabc\r\n");
        typedef or_< newline<>, any<> > newline_any;
        BOOST_FOREACH(
            boost::sub_range<std::string> rng,
            text|tokenized< newline_any >()
        )
        {
            BOOST_CHECK( oven::distance(rng) == 1 || oven::distance(rng) == 2 );
        }
    }

    {
        std::string text; // empty
        BOOST_FOREACH (
            boost::sub_range<std::string> rng,
            biscuit::make_token_range< any<> >(text)
        )
        {
            BOOST_CHECK(false);
        }
    }

    {
        using namespace biscuit;

        std::string text("abcde");
        std::string result;
        typedef or_< newline<>, any<> > newline_any;
        BOOST_FOREACH(
            boost::sub_range<std::string> rng,
            text|tokenized< newline_any >()
        )
        {
            result.push_back(*boost::begin(rng));
        }

        BOOST_CHECK(text == result);
    }
#endif

    {
        using namespace biscuit;

        std::string text("int");
        BOOST_FOREACH(
            boost::sub_range<std::string> rng,
            text|tokenized< any<> >()
        )
        { }
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
