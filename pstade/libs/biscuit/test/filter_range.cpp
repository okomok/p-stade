#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/biscuit/algorithm/match.hpp>
#include <pstade/biscuit/parser.hpp>
#include <pstade/biscuit/range/filter_range.hpp>


#include <functional>
#include <string>
#include <boost/range.hpp>
#include <boost/range/concepts.hpp>
#include <pstade/oven/literal_range.hpp>
#include <pstade/oven/transform_range.hpp>


using namespace pstade;
using namespace pstade::biscuit;


struct toupper_ :
    std::unary_function<char, char>
{
    char operator()(char ch) const { return std::toupper(ch, std::locale()); }
};


struct c_comment :
    seq<
        chseq<'/','*'>,
        star_until< any, chseq<'*','/'> >
    >
{ };


struct c_comment_n :
    seq2<
        chseq2<'/','*'>,
        star_until< any, chseq2<'*','/'> >
    >
{ };


struct isspace_
{
    template< class Range, class U >
    bool operator()(Range& r, U&) const
    {
        return *(boost::begin(r)) == ' ';
    }
};


#define SRC_TEXT_TINY \
    " x      x x xx    " \
/**/


#define SRC_TEXT_COMMENT \
"  /* c comment no.1 */ int i; /* c comment no.2 */ i = 1; /* c comment no.3 */ ++i;  " 
/**/


void test()
{
    // concept check
    //
    {
        typedef filter_range< any, std::string > rng_t;
        boost::function_requires< boost::ForwardRangeConcept<rng_t> >();
    }

    // variadic forms
    //
    {
        std::string text(SRC_TEXT_TINY);
        filter_range< not_< require<any, isspace_> >, std::string > rng(text);
        BOOST_CHECK(( biscuit::match< repeat< chseq<'x'>, 5 > >(rng) ));
    }

    {
        const std::string text(SRC_TEXT_COMMENT);
        filter_range<c_comment, const std::string> rng(text);
        BOOST_ASSERT(( biscuit::match< repeat<c_comment, 3> >(rng) ));
    }

    // numbererd forms
    //
    {
        const std::string text(SRC_TEXT_TINY);
        filter_range< not_< require<any, isspace_> >, const std::string > rng(text);
        BOOST_CHECK(( biscuit::match< repeat< chseq1<'x'>, 5 > >(rng) ));
    }

    {
        std::string text(SRC_TEXT_COMMENT);
        filter_range<c_comment_n, std::string> rng(text);
        BOOST_CHECK(( biscuit::match< repeat<c_comment_n, 3> >(rng) ));
    }

    {
        std::string text; // empty
        filter_range<c_comment_n, std::string> rng(text);
        BOOST_CHECK(( biscuit::match< eps >(rng) ));
    }

    { // scanner chain
        BOOST_CHECK((
            biscuit::match< chseq3<'x','y','z'> >(
                "x  y     z" |
                    oven::as_literal |
                    biscuit::filtered< not_< require<any, isspace_> > >()
            )
        ));
    }
    
    { // scanner chain
        BOOST_CHECK((
            biscuit::match< chseq<'x','y','z'> >(
                biscuit::make_filter_range< not_<space> >(
                    "x  y     z"|oven::as_literal
                )
            )
        ));
    
        BOOST_CHECK((
            biscuit::match< chseq<'x','y','z'> >(
                biscuit::make_filter_range< not_< chset<'&','.','%'> > >(
                    biscuit::make_filter_range< not_<space> >(
                        biscuit::make_filter_range< not_<digit> >(
                            "x & 4 y . 125 %  z"|oven::as_literal
                        )
                    )
                )
            )
        ));
    }

    { // adaptor chain
        BOOST_CHECK((
            biscuit::match< chseq<'x','y','z'> >(
                "x & 4 y . 125 %  z" |
                    oven::as_literal |
                    biscuit::filtered< not_<digit> >() |
                    biscuit::filtered< not_<space> >() |
                    biscuit::filtered< not_< chset<'&','.','%'> > >()
            )
        ));
    }

    {
        BOOST_CHECK((
            biscuit::match< repeat< char_<'D'>, 3 > >(
                "abcdabcdabcd" |
                    oven::as_literal |
                    biscuit::filtered< not_< char_<'a'> > >() |
                    biscuit::filtered< not_< char_<'b'> > >() |
                    biscuit::filtered< not_< char_<'c'> > >() |
                    oven::transformed(toupper_())
            )
        ));
    }
}


int test_main(int, char*[])
{
    ::test();
    return 0;
}
