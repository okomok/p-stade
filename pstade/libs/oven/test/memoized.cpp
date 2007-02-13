#include <pstade/vodka/drink.hpp>


#if defined(__MINGW32__)
    #define PSTADE_WINE_TEST_MINIMAL
#endif

#if !defined(PSTADE_WINE_TEST_MINIMAL)
    #include <boost/test/test_tools.hpp>
    #define BOOST_LIB_NAME boost_test_exec_monitor
    #include <boost/config/auto_link.hpp>
#else
    #include <boost/test/minimal.hpp>
#endif


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/tests.hpp>
#include <pstade/oven/memoized.hpp>
#include <pstade/oven/memoize_iterator.hpp>


#include <string>
#include <iostream>
#include <sstream>
#include <boost/range.hpp>
#include <pstade/oven/functions.hpp>
#include <pstade/oven/copy_range.hpp>
#include <pstade/oven/copied_out.hpp>
#include <pstade/oven/filtered.hpp>
#include <pstade/oven/stream_input.hpp>
#include <pstade/oven/io.hpp>
#include <pstade/oven/taken.hpp>


#include <iterator>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>


// Thanks to: Boost.Spirit 'multi_pass' test
//

#include <boost/scoped_ptr.hpp>


void test_default_multi_pass()
{
    typedef std::stringstream sstream_t;
    using std::istream_iterator;
    using std::endl;

    typedef pstade::oven::memoize_iterator<istream_iterator<char> > default_multi_pass_t;

    sstream_t res;

    res << "-*= test_default_multi_pass =*-\n";
    istream_iterator<char> end;
    boost::scoped_ptr<default_multi_pass_t> mpend(new default_multi_pass_t(end));

    {
        sstream_t ss;
        ss << "test string";

        istream_iterator<char> a(ss);
        boost::scoped_ptr<default_multi_pass_t> mp1(new default_multi_pass_t(a));

        while (*mp1 != *mpend)
        {
            res << *((*mp1)++);
        }

        res << endl;
    }

#if 0 // can't make two forward iterators from *one* input iterator.
    {
        sstream_t ss;
        ss << "test string";
        istream_iterator<char> b(ss);
        boost::scoped_ptr<default_multi_pass_t> mp2(new default_multi_pass_t(b));
        boost::scoped_ptr<default_multi_pass_t> mp3(new default_multi_pass_t(b));
        *mp3 = *mp2;

        for (int i = 0; i < 4; ++i)
        {
            res << **mp2;
            ++*mp2;
        }

        mp3.reset();

        while (*mp2 != *mpend)
        {
            res << **mp2;
            ++*mp2;
        }

        res << endl;
    }
#endif

    {
        sstream_t ss;
        ss << "test string";
        istream_iterator<char> a(ss);
        boost::scoped_ptr<default_multi_pass_t> mp1(new default_multi_pass_t(a));
        boost::scoped_ptr<default_multi_pass_t> mp2(new default_multi_pass_t(*mp1));

        for (int i = 0; i < 4; ++i)
        {
            res << **mp1;
            ++*mp1;
        }

        while (*mp2 != *mpend)
        {
            res << **mp2;
            ++*mp2;
        }

        while (*mp1 != *mpend)
        {
            res << **mp1;
            ++*mp1;
        }

        res << endl;
    }

    {
        sstream_t ss;
        ss << "test string";
        istream_iterator<char> b(ss);
        boost::scoped_ptr<default_multi_pass_t> mp2(new default_multi_pass_t(b));
        boost::scoped_ptr<default_multi_pass_t> mp3(new default_multi_pass_t(b));
        *mp3 = *mp2;

        for (int i = 0; i < 4; ++i)
        {
            res << **mp2;
            ++*mp2;
        }

        mp3.reset();
        ++*mp2;

        while (*mp2 != *mpend)
        {
            res << **mp2;
            ++*mp2;
        }

        res << endl;
    }

    {
        sstream_t ss;
        ss << "test string";
        istream_iterator<char> a(ss);
        boost::scoped_ptr<default_multi_pass_t> mp1(new default_multi_pass_t(a));
        boost::scoped_ptr<default_multi_pass_t> mp2(new default_multi_pass_t(*mp1));

        BOOST_CHECK(*mp1 == *mp2);
//        BOOST_CHECK(*mp1 >= *mp2);
//        BOOST_CHECK(*mp1 <= *mp2);
        for (int i = 0; i < 4; ++i)
        {
            res << **mp1;
            ++*mp1;
        }

        BOOST_CHECK(*mp1 != *mp2);
//        BOOST_CHECK(*mp1 > *mp2);
//        BOOST_CHECK(*mp1 >= *mp2);
//        BOOST_CHECK(*mp2 < *mp1);
//        BOOST_CHECK(*mp2 <= *mp1);
        while (*mp2 != *mp1)
        {
            res << **mp2;
            ++*mp2;
        }

        BOOST_CHECK(*mp1 == *mp2);
//        BOOST_CHECK(*mp1 >= *mp2);
//        BOOST_CHECK(*mp1 <= *mp2);
        while (*mp1 != *mpend)
        {
            res << **mp1;
            ++*mp1;
        }

        BOOST_CHECK(*mp1 != *mp2);
//        BOOST_CHECK(*mp1 > *mp2);
//        BOOST_CHECK(*mp1 >= *mp2);
//        BOOST_CHECK(*mp2 < *mp1);
//        BOOST_CHECK(*mp2 <= *mp1);
        while (*mp2 != *mpend)
        {
            res << **mp2;
            ++*mp2;
        }

        BOOST_CHECK(*mp1 == *mp2);
//        BOOST_CHECK(*mp1 >= *mp2);
//        BOOST_CHECK(*mp1 <= *mp2);
        res << endl;
    }


    {
#if 0
        sstream_t ss;
        ss << "test string";
        istream_iterator<char> a(ss);
        boost::scoped_ptr<default_multi_pass_t> mp1(new default_multi_pass_t(a));
        boost::scoped_ptr<default_multi_pass_t> mp2(new default_multi_pass_t(a));
        BOOST_CHECK(*mp1 != *mp2);
        ++*mp1;
        BOOST_CHECK(*mp1 != *mp2);

    }

    {
        sstream_t ss;
        ss << "test string";
        istream_iterator<char> b(ss);
        boost::scoped_ptr<default_multi_pass_t> mp2(new default_multi_pass_t(b));
        boost::scoped_ptr<default_multi_pass_t> mp3(new default_multi_pass_t(b));
        *mp3 = *mp2;

        for (int i = 0; i < 4; ++i)
        {
            res << **mp2;
            ++*mp2;
        }
#endif

#if 0 // has no clear_queue nor exception.
        mp2->clear_queue();

        while (*mp2 != *mpend)
        {
            res << **mp2;
            ++*mp2;
        }

        try
        {
            res << **mp3; // this should throw illegal_backtracking
            BOOST_CHECK(0);
        }
        catch (const boost::spirit::multi_pass_policies::illegal_backtracking& /*e*/)
        {
        }
        res << endl;
#endif
    }
}


void test_memoized_default_multi_pass()
{
    typedef std::stringstream sstream_t;
    using std::istream_iterator;
    using std::endl;

    typedef pstade::oven::memoize_iterator<istream_iterator<char>, boost::mpl::true_ > default_multi_pass_t;

    sstream_t res;

    res << "-*= test_default_multi_pass =*-\n";
    istream_iterator<char> end;
        ////
        std::auto_ptr< istream_iterator<char> > Q(new istream_iterator<char>(end));
        ////
    boost::scoped_ptr<default_multi_pass_t> mpend(new default_multi_pass_t(Q.get()));

    {
        sstream_t ss;
        ss << "test string";

        istream_iterator<char> a(ss);
        ////
        std::auto_ptr< istream_iterator<char> > Q(new istream_iterator<char>(a));
        ////
        boost::scoped_ptr<default_multi_pass_t> mp1(new default_multi_pass_t(Q.get()));

        while (*mp1 != *mpend)
        {
            res << *((*mp1)++);
        }

        res << endl;
    }

#if 0 // can't make two forward iterators from *one* input iterator.
    {
        sstream_t ss;
        ss << "test string";
        istream_iterator<char> b(ss);

        boost::scoped_ptr<default_multi_pass_t> mp2(new default_multi_pass_t(b));
        boost::scoped_ptr<default_multi_pass_t> mp3(new default_multi_pass_t(b));
        *mp3 = *mp2;

        for (int i = 0; i < 4; ++i)
        {
            res << **mp2;
            ++*mp2;
        }

        mp3.reset();

        while (*mp2 != *mpend)
        {
            res << **mp2;
            ++*mp2;
        }

        res << endl;
    }
#endif

    {
        sstream_t ss;
        ss << "test string";
        istream_iterator<char> a(ss);
            ////
            std::auto_ptr< istream_iterator<char> > Qa(new istream_iterator<char>(a));
            ////
        boost::scoped_ptr<default_multi_pass_t> mp1(new default_multi_pass_t(Qa.get()));
        boost::scoped_ptr<default_multi_pass_t> mp2(new default_multi_pass_t(*mp1));

        for (int i = 0; i < 4; ++i)
        {
            res << **mp1;
            ++*mp1;
        }

        while (*mp2 != *mpend)
        {
            res << **mp2;
            ++*mp2;
        }

        while (*mp1 != *mpend)
        {
            res << **mp1;
            ++*mp1;
        }

        res << endl;
    }

#if 0 // can't make...
    {
        sstream_t ss;
        ss << "test string";
        istream_iterator<char> b(ss);
        boost::scoped_ptr<default_multi_pass_t> mp2(new default_multi_pass_t(Qb));
        boost::scoped_ptr<default_multi_pass_t> mp3(new default_multi_pass_t(b));
        *mp3 = *mp2;

        for (int i = 0; i < 4; ++i)
        {
            res << **mp2;
            ++*mp2;
        }

        mp3.reset();
        ++*mp2;

        while (*mp2 != *mpend)
        {
            res << **mp2;
            ++*mp2;
        }

        res << endl;
    }
#endif
    {
        sstream_t ss;
        ss << "test string";
        istream_iterator<char> a(ss);
            ////
            std::auto_ptr< istream_iterator<char> > Qa(new istream_iterator<char>(a));
            ////
        boost::scoped_ptr<default_multi_pass_t> mp1(new default_multi_pass_t(Qa.get()));
        boost::scoped_ptr<default_multi_pass_t> mp2(new default_multi_pass_t(*mp1));

        BOOST_CHECK(*mp1 == *mp2);
//        BOOST_CHECK(*mp1 >= *mp2);
//        BOOST_CHECK(*mp1 <= *mp2);
        for (int i = 0; i < 4; ++i)
        {
            res << **mp1;
            ++*mp1;
        }

        BOOST_CHECK(*mp1 != *mp2);
//        BOOST_CHECK(*mp1 > *mp2);
//        BOOST_CHECK(*mp1 >= *mp2);
//        BOOST_CHECK(*mp2 < *mp1);
//        BOOST_CHECK(*mp2 <= *mp1);
        while (*mp2 != *mp1)
        {
            res << **mp2;
            ++*mp2;
        }

        BOOST_CHECK(*mp1 == *mp2);
//        BOOST_CHECK(*mp1 >= *mp2);
//        BOOST_CHECK(*mp1 <= *mp2);
        while (*mp1 != *mpend)
        {
            res << **mp1;
            ++*mp1;
        }

        BOOST_CHECK(*mp1 != *mp2);
//        BOOST_CHECK(*mp1 > *mp2);
//        BOOST_CHECK(*mp1 >= *mp2);
//        BOOST_CHECK(*mp2 < *mp1);
//        BOOST_CHECK(*mp2 <= *mp1);
        while (*mp2 != *mpend)
        {
            res << **mp2;
            ++*mp2;
        }

        BOOST_CHECK(*mp1 == *mp2);
//        BOOST_CHECK(*mp1 >= *mp2);
//        BOOST_CHECK(*mp1 <= *mp2);
        res << endl;
    }


    {
#if 0
        sstream_t ss;
        ss << "test string";
        istream_iterator<char> a(ss);
        boost::scoped_ptr<default_multi_pass_t> mp1(new default_multi_pass_t(a));
        boost::scoped_ptr<default_multi_pass_t> mp2(new default_multi_pass_t(a));
        BOOST_CHECK(*mp1 != *mp2);
        ++*mp1;
        BOOST_CHECK(*mp1 != *mp2);

    }

    {
        sstream_t ss;
        ss << "test string";
        istream_iterator<char> b(ss);
        boost::scoped_ptr<default_multi_pass_t> mp2(new default_multi_pass_t(b));
        boost::scoped_ptr<default_multi_pass_t> mp3(new default_multi_pass_t(b));
        *mp3 = *mp2;

        for (int i = 0; i < 4; ++i)
        {
            res << **mp2;
            ++*mp2;
        }
#endif

#if 0 // has no clear_queue nor exception.
        mp2->clear_queue();

        while (*mp2 != *mpend)
        {
            res << **mp2;
            ++*mp2;
        }

        try
        {
            res << **mp3; // this should throw illegal_backtracking
            BOOST_CHECK(0);
        }
        catch (const boost::spirit::multi_pass_policies::illegal_backtracking& /*e*/)
        {
        }
        res << endl;
#endif
    }
}


void test()
{
    ::test_default_multi_pass();
    ::test_memoized_default_multi_pass();

    namespace oven = pstade::oven;
    using namespace oven;
    namespace bll = boost::lambda;

    {
        std::string ans("18284610528192");
        std::stringstream ss;
        ss << ans;
        std::vector<char> expected = ans|copied;
        BOOST_CHECK( oven::test_Forward_Readable(
            oven::stream_input<char>(ss)|memoized,
            expected
        ) );
    }
    {
        int const src[] = { 1,2,5,3,6,8,6,1 };
        memo_table tb;

        int const ans[] = { 1,2,5,3,6 };
        std::vector<int> expected = ans|copied;
        BOOST_CHECK( oven::test_Forward_Readable(
            src|memoized(tb)|taken(5),
            expected
        ) );
    }
    {
        std::string ans("18284610528192");
        memo_table tb;

        std::vector<char> expected = ans|copied;
        BOOST_CHECK( oven::test_Forward_Readable(
            ans|memoized(tb),
            expected
        ) );
    }
#if 0 // legacy
    {
        std::string ans("18284610528192");
        std::stringstream ss;
        memo_table to_table;
        ss << ans;
        std::vector<char> expected = ans|copied;
        BOOST_CHECK( oven::test_Forward_Readable(
            oven::stream_input<char>(ss)|memoized(to_table),
            expected
        ) );
    }
#endif
    {
        std::string src("axaxaxbxbxbx");
        std::string s1; // snapshot
        std::string s2;
        std::string answer("bbb");

        BOOST_CHECK((
            oven::equals(answer,
                src |
                    filtered(regular(bll::_1 != 'x')) |
                    memoized |
                    copied_out(std::back_inserter(s1)) |
                    filtered(regular(bll::_1 != 'a')) |
                    memoized |
                    copied_out(std::back_inserter(s2))
            )
        ));

        BOOST_CHECK( s1 == "aaabbb" );
        BOOST_CHECK( s2 == answer );
    }
}


#if !defined(PSTADE_WINE_TEST_MINIMAL)

    #include <boost/test/unit_test.hpp>
    using boost::unit_test::test_suite;

    test_suite *
    init_unit_test_suite(int argc, char *argv[])
    {
        test_suite *test = BOOST_TEST_SUITE("Wine Test Suite");
        test->add(BOOST_TEST_CASE(&::test));

        (void)argc, (void)argv; // unused
        return test;
    }

#else

    int test_main(int, char*[])
    {
        ::test();
        return 0;
    }

#endif
