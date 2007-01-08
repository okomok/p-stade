#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/detail/template_arguments_for_broken.hpp>


#include <pstade/biscuit/parser.hpp>
#include <pstade/biscuit/algorithm/match.hpp>


#include <string>
#include <vector>


#include <pstade/oven.hpp>


#include <boost/assign/std/vector.hpp>
#include <boost/algorithm/string.hpp>


#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    #define ITERATOR_RANGE_CONSTRUCTOR_IS_BROKEN
#endif


void test()
{
    using namespace pstade;
    using namespace biscuit;

    // normal parsers
    //
    {
        std::string str("abcxabcx");

        BOOST_CHECK((
            biscuit::match<
                seq4<
                    capture< 1, star_before< any, char_<'x'> > >,
                    char_<'x'>,
                    backref<1>,
                    char_<'x'>
                >
            >(str)
        ));
    }

    {
        std::string str("abcxabcabcabc");

        BOOST_CHECK((
            biscuit::match<
                seq3<
                    capture< 1, star_before< any, char_<'x'> > >,
                    char_<'x'>,
                    repeat< backref<1>, 3 >
                >
            >(str)
        ));
    }

    {
        std::string str("ab123cxab123cxab123cxab123cx");

        BOOST_CHECK((
            biscuit::match<
                seq3<
                    as_filtered<
                        capture< 1, chseq3<'a','b','c'> >,
                        alpha_com
                    >,
                    char_<'x'>,
                    repeat< seq2< backref<1>, char_<'x'> >, 3 >
                >
            >(str)
        ));
    }

    // directives
    //
    {
        std::string str("99ab123cxab123cxab123cxab123cx");

        BOOST_CHECK((
            biscuit::match<
                seq<
                    chseq<'9','9'>,
                    as_transformed<
                        as_filtered<
                            capture< 1, chseq2<'A','B'> >,
                            alpha_com
                        >,
                        to_upper<char>
                    >,
                    chseq2<'c','x'>,
                    repeat< seq2< backref<1>, chseq2<'c','x'> >, 3 >
                >
            >(str)
        ));
    }

    {
        std::string str("ab123cxab123cxab123cxab123cx");

        BOOST_CHECK((
            biscuit::match<
                seq3<
                    capture< 1, as_filtered< star_before< any, char_<'x'> >, alpha_com > >,
                    char_<'x'>,
                    repeat< seq2< backref<1>, char_<'x'> >, 3 >
                >
            >(str)
        ));
    }

    {
        std::string str("99ab123cxab123cxab123cxab123cx");
        match_results<std::string> caps;

        BOOST_CHECK((
            biscuit::results_match<
                seq4<
                    chseq2<'9','9'>,
                    as_filtered<
                        capture< 1, chseq3<'a','b','c'> >,
                        alpha_com
                    >,
                    char_<'x'>,
                    repeat< seq2< backref<1>, char_<'x'> >, 3 >
                >
            >(str, caps)
        ));
    }

#if !defined(ITERATOR_RANGE_CONSTRUCTOR_IS_BROKEN)
    {
        std::string val2("DDD");
        std::string val3("E");
        match_results<std::string> caps;
        caps[2] = val2;
        caps[3] = val3;
        std::string str("ab123cxab123cxab123cxDDDE");

        BOOST_CHECK((
            biscuit::results_match<
                seq5<
                    capture< 1, as_filtered< star_before< any, char_<'x'> >, alpha_com > >,
                    char_<'x'>,
                    repeat< seq2< backref<1>, char_<'x'> >, 2 >,
                    backref<2>,
                    backref<3>
                >
            >(str, caps)
        ));


        BOOST_CHECK( oven::equal(caps[1], "ab123c") );
    }
#endif

    {
        std::string str("ab123cxab123cxab123cxab123cx");

        BOOST_CHECK((
            biscuit::match<
                seq3<
                    capture< 1,
                        as_transformed<
                            as_filtered< chseq3<'A','B','C'>, alpha_com >,
                            to_upper<char>
                        >
                    >,
                    char_<'x'>,
                    repeat< seq2< backref<1>, char_<'x'> >, 3 >
                >
            >(str)
        ));
    }

    {
        std::string const str("ab123cxab123cxab123cxab123cx");

        BOOST_CHECK((
            biscuit::match<
                seq3<
                    capture< 1,
                        as_transformed<
                            as_filtered< chseq3<'A','B','C'>, alpha_com >,
                            to_upper<char>
                        >
                    >,
                    char_<'x'>,
                    repeat< seq2< backref<1>, char_<'x'> >, 3 >
                >
            >(str)
        ));
    }

    {
        match_results<std::string> caps;
        std::string str("abcxabcx");

        BOOST_CHECK((
            biscuit::results_match<
                seq4<
                    capture< 1, star_before< any, char_<'x'> > >,
                    char_<'x'>,
                    capture< 2, backref<1> >,
                    char_<'x'>
                >
            >(str, caps)
        ));

#if !defined(ITERATOR_RANGE_CONSTRUCTOR_IS_BROKEN)
        BOOST_CHECK( oven::equal(caps[1], "abc") );
        boost::to_upper(caps[1]);
        BOOST_CHECK( oven::equal(str, "ABCxabcx") );
        boost::to_upper(caps[2]);
        BOOST_CHECK( oven::equal(str, "ABCxABCx") );
#endif
    }

    {
        match_results<char const *> cap;

        BOOST_CHECK((
            !biscuit::match< no_captures<
                seq4<
                    capture< 1, star_before< any, char_<'x'> > >,
                    char_<'x'>,
                    backref<1>,
                    char_<'x'>
                >
            > >("abcxabcx"|oven::as_literal)
        ));
    }   

    {
        match_results<char const *> cap;

        BOOST_CHECK((
            biscuit::results_match<
                seq4<
                    capture< 1, star_before< any, char_<'x'> > >,
                    char_<'x'>,
                    backref<1>,
                    char_<'x'>
                >
            >("abcxabcx"|oven::as_literal, cap)
        ));

#if !defined(ITERATOR_RANGE_CONSTRUCTOR_IS_BROKEN)
        BOOST_CHECK( oven::equal(cap[1], "abc") );
#endif
    }

    // with any::value
    //
    {
        typedef
            seq<
                repeat<chseq<'z'>, 3>,
                repeat<
                    capture< any::value, star_until< any, char_<'x'> > >,
                    3
                >,
                backref< any::value >
            >
        parser_t;

        {
            std::string str("zzzABCx12xPQRxABCx");
            BOOST_CHECK((
                biscuit::match<parser_t>(str)
            ));
        }
        {
            std::string str("zzzABCx12xPQRx12x");
            BOOST_CHECK((
                biscuit::match<parser_t>(str)
            ));
        }
        {
            std::string str("zzzABCx12xPQRxPQRx");
            BOOST_CHECK((
                biscuit::match<parser_t>(str)
            ));
        }
    }
}


int test_main(int, char*[])
{
    ::test();

    return 0;
}
