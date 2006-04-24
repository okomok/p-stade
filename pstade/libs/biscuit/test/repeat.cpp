#include <pstade/vodka/begin.hpp>
#include <boost/test/minimal.hpp>


// PStade.Biscuit
//
// Copyright MB 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/algorithm/match.hpp>
#include <pstade/biscuit/parser.hpp>


#include <string>


void test()
{
    using namespace pstade;
    using namespace biscuit;

    {
        std::string text("xxxxx");
        BOOST_CHECK(( biscuit::match< repeat< chseq1<'x'>, 4, 6 > >(text) ));
        BOOST_CHECK(( biscuit::match< repeat< chseq1<'x'>, 5, 5 > >(text) ));
        BOOST_CHECK(( biscuit::match< repeat< chseq1<'x'>, 5 > >(text) ));
        BOOST_CHECK(( biscuit::match< repeat< chseq1<'x'>, 0, 5 > >(text) ));
        BOOST_CHECK(( biscuit::match< repeat< chseq1<'x'>, 1, 200 > >(text) ));
        BOOST_CHECK(( biscuit::match< repeat< chseq1<'x'>, 5, 500 > >(text) ));

        BOOST_CHECK(( !biscuit::match< repeat< chseq1<'x'>, 2, 4 > >(text) ));
        BOOST_CHECK(( !biscuit::match< repeat< chseq1<'x'>, 0, 4 > >(text) ));
        BOOST_CHECK(( !biscuit::match< repeat< chseq1<'x'>, 4 > >(text) ));
        BOOST_CHECK(( !biscuit::match< repeat< chseq1<'x'>, 6, 100 > >(text) ));
        BOOST_CHECK(( !biscuit::match< repeat< chseq1<'x'>, 40, 200 > >(text) ));

        BOOST_CHECK(( !biscuit::match< max_repeat< chseq1<'x'>, 4 > >(text) ));
        BOOST_CHECK(( biscuit::match< max_repeat< chseq1<'x'>, 5 > >(text) ));
        BOOST_CHECK(( biscuit::match< max_repeat< chseq1<'x'>, 6 > >(text) ));
        BOOST_CHECK(( biscuit::match< max_repeat< chseq1<'x'>, 7 > >(text) ));
    }

    typedef seq2<
        chseq2<'/','*'>,
        star_until< any, chseq2<'*','/'> >
    > c_comment;

    {
        std::string text("/* c comment no.1 *//* c comment no.2 *//* c comment no.3 */");
        BOOST_CHECK(( biscuit::match< repeat< c_comment, 1, 6 > >(text) ));
        BOOST_CHECK(( biscuit::match< repeat< c_comment, 1, 3 > >(text) ));
        BOOST_CHECK(( biscuit::match< repeat< c_comment, 3 > >(text) ));
        BOOST_CHECK(( biscuit::match< repeat< c_comment, 3, 600 > >(text) ));
        BOOST_CHECK(( biscuit::match< repeat< c_comment, 2, 50 > >(text) ));


        BOOST_CHECK(( !biscuit::match< repeat< c_comment, 2, 2 > >(text) ));
        BOOST_CHECK(( !biscuit::match< repeat< c_comment, 1, 2 > >(text) ));
        BOOST_CHECK(( !biscuit::match< repeat< c_comment, 100, 200 > >(text) ));
        BOOST_CHECK(( !biscuit::match< repeat< c_comment, 0 > >(text) ));
        BOOST_CHECK(( !biscuit::match< repeat< c_comment, 4, 200 > >(text) ));

        BOOST_CHECK(( biscuit::match< min_repeat< c_comment, 3 > >(text) ));
        BOOST_CHECK(( !biscuit::match< min_repeat< c_comment, 4 > >(text) ));
    }

    {
        const std::string text("/* c comment no.1 *//* c comment no.2 *//* c comment no.3 */xxxxx");
        BOOST_CHECK(( biscuit::match< seq2< repeat< c_comment, 1, 6 >, repeat< chseq1<'x'>, 3, 5 > > >(text) ));
        BOOST_CHECK(( biscuit::match< seq2< repeat< c_comment, 1, 60 >, repeat< chseq1<'x'>, 0, 10 > > >(text) ));
        BOOST_CHECK(( biscuit::match< seq2< repeat< c_comment, 0, 30 >, repeat< chseq1<'x'>, 3, 50 > > >(text) ));
        BOOST_CHECK(( biscuit::match< seq2< repeat< c_comment, 3 >, repeat< chseq1<'x'>, 5 > > >(text) ));
        BOOST_CHECK(( biscuit::match< seq2< repeat< c_comment, 3, 60 >, repeat< chseq1<'x'>, 5, 50 > > >(text) ));

        BOOST_CHECK(( !biscuit::match< seq2< repeat< c_comment, 1, 2 >, repeat< chseq1<'x'>, 3, 5 > > >(text) ));
        BOOST_CHECK(( !biscuit::match< seq2< repeat< c_comment, 6, 6 >, repeat< chseq1<'x'>, 0, 10 > > >(text) ));
        BOOST_CHECK(( !biscuit::match< seq2< repeat< c_comment, 3 >, repeat< chseq1<'x'>, 3 > > >(text) ));
        BOOST_CHECK(( !biscuit::match< seq2< repeat< c_comment, 0 >, repeat< chseq1<'x'>, 5 > > >(text) ));
        BOOST_CHECK(( !biscuit::match< seq2< repeat< c_comment, 0, 60 >, repeat< chseq1<'x'>, 6, 50 > > >(text) ));
    }

    typedef seq2<
        chseq4<'<','!','-','-'>,
        star_until<
            or_2<
                minus2< any, chseq1<'-'> >,
                seq2<
                    chseq1<'-'>,
                    minus2< any, chseq1<'-'> >
                >
            >,
            chseq3<'-','-','>'>
        >
    > xml_comment;

    typedef seq3<
        chseq4<'<','!','-','-'>,
        star<
            or_2<
                minus2< any, chseq1<'-'> >,
                seq2<
                    chseq1<'-'>,
                    minus2< any, chseq1<'-'> >
                >
            >
        >,
        chseq3<'-','-','>'>
    > xml_comment2;

    {
        std::string text("<!-- xml comment no.1 --><!-- xml comment no.2 -->");
        BOOST_CHECK(( biscuit::match< repeat< xml_comment, 2, 2 > > (text) ));
        BOOST_CHECK(( biscuit::match< repeat< xml_comment, 2, 60 > >(text) ));
        BOOST_CHECK(( biscuit::match< repeat< xml_comment, 0, 30 > >(text) ));
        BOOST_CHECK(( biscuit::match< repeat< xml_comment2, 2 > >(text) ));
        BOOST_CHECK(( biscuit::match< repeat< xml_comment, 1, 60 > >(text) ));

        BOOST_CHECK(( !biscuit::match< repeat< xml_comment, 1, 1 > >(text) ));
        BOOST_CHECK(( !biscuit::match< repeat< xml_comment, 6, 6 > >(text) ));
        BOOST_CHECK(( !biscuit::match< repeat< xml_comment, 3 > >(text) ));
        BOOST_CHECK(( !biscuit::match< repeat< xml_comment2, 50 > >(text) ));
        BOOST_CHECK(( !biscuit::match< repeat< xml_comment, 0, 0 > >(text) ));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
