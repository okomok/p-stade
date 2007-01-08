#include <pstade/vodka/drink.hpp>


// PStade.Biscuit
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven/detail/boost_begin_end.hpp>


#include <iostream> // cout


#include <pstade/biscuit.hpp>
#include <pstade/check.hpp>
#include <pstade/oven.hpp>


using namespace pstade;
using namespace biscuit;
using biscuit::minus; // workaround for VC++.
using biscuit::plus;


// test_introduction
//
struct integer : seq< opt< or_< char_<'+'>, char_<'-'> > >, biscuit::plus<digit> > { };

struct expression ;
struct group      : seq< char_<'('>, expression, char_<')'> > { };
struct factor     : or_< integer, group > { };
struct term       : seq< factor, star< or_< seq< char_<'*'>, factor >, seq< char_<'/'>, factor > > > > { };
struct expression : seq< term, star< or_< seq< char_<'+'>, term >, seq< char_<'-'>, term > > > > { };

struct skip_space : biscuit::not_<space> { };

struct S :
    or_<
        seq< chseq<'('>, S, chseq<')'> , S >,
        eps
    >
{ };

void test_introduction()
{
    PSTADE_CHECK( biscuit::match<expression>( "12345"|oven::as_literal|biscuit::filtered<skip_space>() ) );
    PSTADE_CHECK( biscuit::match<expression>( "-12345"|oven::as_literal|biscuit::filtered<skip_space>() ) );
    PSTADE_CHECK( biscuit::match<expression>( "+12345"|oven::as_literal|biscuit::filtered<skip_space>() ) );
    PSTADE_CHECK( biscuit::match<expression>( "1 + 2"|oven::as_literal|biscuit::filtered<skip_space>() ) );
    PSTADE_CHECK( biscuit::match<expression>( "1 * 2"|oven::as_literal|biscuit::filtered<skip_space>() ) );
    PSTADE_CHECK( biscuit::match<expression>( "1/2 + 3/4"|oven::as_literal|biscuit::filtered<skip_space>() ) );
    PSTADE_CHECK( biscuit::match<expression>( "1 + 2 + 3 + 4"|oven::as_literal|biscuit::filtered<skip_space>() ) );
    PSTADE_CHECK( biscuit::match<expression>( "1 * 2 * 3 * 4"|oven::as_literal|biscuit::filtered<skip_space>() ) );
    PSTADE_CHECK( biscuit::match<expression>( "(1 + 2) * (3 + 4)"|oven::as_literal|biscuit::filtered<skip_space>() ) );
    PSTADE_CHECK( biscuit::match<expression>(  "(-1 + 2) * (3 + -4)"|oven::as_literal|biscuit::filtered<skip_space>() ) );
    PSTADE_CHECK( biscuit::match<expression>( "1 + ((6 * 200) - 20) / 6"|oven::as_literal|biscuit::filtered<skip_space>() ) );
    PSTADE_CHECK( biscuit::match<expression>( "(1 + (2 + (3 + (4 + 5))))"|oven::as_literal|biscuit::filtered<skip_space>() ) );
    PSTADE_CHECK( !biscuit::match<expression>( "(1 + (2 + (3 + (4 + 5)))"|oven::as_literal|biscuit::filtered<skip_space>() ) );

    PSTADE_CHECK( biscuit::match< S >("(()())") );
    PSTADE_CHECK( biscuit::match< S >("(()()(())()())") );
    PSTADE_CHECK( !biscuit::match< S >("(()()))") );
}


// test_quick_start
//
#include <string>

typedef seq<
    chseq<'/','*'>,
    star_until< any, chseq<'*','/'> >
> c_comment;

void test_quick_start()
{
    std::string text("/* Hello, Biscuit! */");
    if (biscuit::match<c_comment>(text)) {
        // ...
    }
}


// test_actor
//
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <boost/range/begin.hpp>
#include <pstade/oven.hpp>

using biscuit::minus; // workaround for VC++.
using biscuit::plus;

struct decorate_action
{
  void operator()(boost::sub_range<std::string> rng, std::stringstream& out)
  {
    out << "[" << oven::copy_range<std::string>(rng) << "]";
    boost::to_upper(rng);
  }
};

struct xml_comment :
    seq<
        chseq<'<','!','-','-'>,
        star<
            or_<
                biscuit::minus< any, chseq<'-'> >,
                seq<
                    chseq<'-'>,
                    biscuit::minus< any, chseq<'-'> >
                >
            >
        >,
        chseq<'-','-','>'>
    >
{ };

struct xml_comment_action :
    actor< xml_comment, decorate_action >
{ };

void test_actor()
{
    std::string text("<!-- xml comment -->");
    std::stringstream out;
    PSTADE_CHECK( biscuit::match<xml_comment_action>(text, out) );
    PSTADE_CHECK( oven::equal(out.str(), "[<!-- xml comment -->]") );
    PSTADE_CHECK( oven::equal(text, "<!-- XML COMMENT -->") );
}


// test_match
//
void test_match()
{
    PSTADE_CHECK( biscuit::match<xml_comment>("<!-- hello, xml comment -->"|oven::as_literal) );
    PSTADE_CHECK( !biscuit::match<xml_comment>("<!-- not well-formed comment -- -->"|oven::as_literal) );
}


// test_search
//
void test_search()
{
    std::string text("  int i; /* c comment */ int j; ");
    boost::sub_range<std::string> rng = biscuit::search<c_comment>(text);
    PSTADE_CHECK( oven::equal(rng, "/* c comment */") );
}


// test_search
//
void test_iterate()
{
    std::stringstream out; {
        std::string text(" <hello> <!-- xml comment no.1 --> biscuit</hello> <wow>biscuit</wow> <!-- xml comment no.2 -->  ");
        biscuit::iterate<xml_comment_action>(text, out, biscuit::output_action());
    }
    PSTADE_CHECK( oven::equal(out.str(), " <hello> [<!-- xml comment no.1 -->] biscuit</hello> <wow>biscuit</wow> [<!-- xml comment no.2 -->]  ") );
}


// test_filter_range
//
#include <functional>
#include <locale>

struct toupper_fun : std::unary_function<char, char>
{
    char operator()(char ch) const { return std::toupper(ch, std::locale()); }
};

void test_filter_range()
{
    std::string text("  /* c comment no.1 */ int i; /* c comment no.2 */ i = 1; /* c comment no.3 */ ++i;  ");
    filter_range<c_comment, std::string> comments(text);
    PSTADE_CHECK(( biscuit::match< repeat<c_comment, 3> >(comments) ));

    PSTADE_CHECK((
        biscuit::match< chseq<'x','y','z'> >(
            biscuit::make_filter_range< biscuit::not_< chset<'&','.','%'> > >(
                biscuit::make_filter_range< biscuit::not_<space> >(
                    biscuit::make_filter_range< biscuit::not_<digit> >(
                        "x & 4 y . 125 %  z"|oven::as_literal
                    )
                )
            )
        )
    ));

    PSTADE_CHECK((
        biscuit::match< repeat< char_<'D'>, 3 > >(
            "abcdabcdabcd" |
                oven::as_literal |
                biscuit::filtered< biscuit::not_< char_<'a'> > >() |
                biscuit::filtered< biscuit::not_< char_<'b'> > >() |
                biscuit::filtered< biscuit::not_< char_<'c'> > >() |
                oven::transformed(toupper_fun())
        )
    ));
}


// test_token_range
//
#include <boost/foreach.hpp>

void test_token_range()
{
    std::string text("  /* c comment no.1 */int i; /* c comment no.2 */i = 1; /* c comment no.3 */ ++i;  ");
    token_range<c_comment, std::string> comments(text);
    BOOST_FOREACH (boost::sub_range<std::string> rng, comments) {
        std::cout << oven::copy_range<std::string>(rng) << std::endl;
    }

    BOOST_FOREACH (
        boost::iterator_range<const char *> rng,
        "  /* c comment no.1 */int i; /* c comment no.2 */i = 1; /* c comment no.3 */ ++i;  " |
            oven::as_literal |
            biscuit::tokenized<c_comment>()
    ) {
        std::cout << oven::copy_range<std::string>(rng) << std::endl;
    }
}


// test_capturing
//
void test_capturing()
{
    match_results<std::string> caps;
    std::string text("abcxabcx");

    PSTADE_CHECK((
        biscuit::results_match<
            seq<
                capture< 1, star_before< any, char_<'x'> > >,
                char_<'x'>,
                capture< 2, backref<1> >,
                char_<'x'>
            >
        >(text, caps)
    ));

    PSTADE_CHECK( oven::equal(caps[1], "abc") );
    boost::to_upper(caps[1]);
    PSTADE_CHECK( oven::equal(text, "ABCxabcx") );
    boost::to_upper(caps[2]);
    PSTADE_CHECK( oven::equal(text, "ABCxABCx") );
}


// test_valseq
//
#include <vector>
#include <boost/assign.hpp>

template< int i >
struct value_at_
{
    std::string& operator()(std::vector<std::string>& values)
    {
        return values.at(i);
    }
};

void test_valseq()
{
    using namespace boost::assign;

    std::vector<std::string> inputs; { inputs += "ghi", "abc"; }
    std::vector<std::string> values; { values += "abc", "def", "ghi"; }
  
    PSTADE_CHECK(( biscuit::match< valseq< value_at_<2>, value_at_<0> > >(inputs, values) ));
}


// test_valset
//
void test_valset()
{
    using namespace boost::assign;

    std::vector<std::string> inputs0; { inputs0 += "abc"; }
    std::vector<std::string> inputs1; { inputs1 += "def"; }
    std::vector<std::string> inputs2; { inputs2 += "ghi"; }
    std::vector<std::string> values; { values += "abc", "def", "ghi"; }

    PSTADE_CHECK(( biscuit::match< valset< value_at_<0>, value_at_<1>, value_at_<2> > >(inputs0, values) ));
    PSTADE_CHECK(( biscuit::match< valset< value_at_<0>, value_at_<1>, value_at_<2> > >(inputs1, values) ));
    PSTADE_CHECK(( biscuit::match< valset< value_at_<0>, value_at_<1>, value_at_<2> > >(inputs2, values) ));
}


// test_seq_range
//
struct pattern_loader
{
    std::string& operator()(std::string& pattern)
    {
        pattern += "c";
        return pattern;
    }
};

void test_seq_range()
{
    std::string pattern("ab");
    PSTADE_CHECK(( biscuit::match< seq< chseq<'x'>, seq_range<pattern_loader>, chseq<'y'> > >("xabcy"|oven::as_literal, pattern) ));
}


// test_set_range
//
void test_set_range()
{
    std::string pattern("ab");
    PSTADE_CHECK(( biscuit::match< seq< chseq<'x'>, set_range<pattern_loader>, chseq<'y'> > >("xay"|oven::as_literal, pattern) ));
    PSTADE_CHECK(( biscuit::match< seq< chseq<'x'>, set_range<pattern_loader>, chseq<'y'> > >("xby"|oven::as_literal, pattern) ));
    PSTADE_CHECK(( biscuit::match< seq< chseq<'x'>, set_range<pattern_loader>, chseq<'y'> > >("xcy"|oven::as_literal, pattern) ));
}


// test_error_handling
//
struct handler
{
  template< class State, class UserState >
  error_status operator()(State&, UserState&, boost::sub_range<std::string> rng, int id)
  {
    PSTADE_CHECK( id == 3 );
    boost::to_lower(rng);
    std::cout << "exception caught...Test concluded successfully" << std::endl;
    return error_retry;
  }
};

void test_error_handling()
{
    typedef guard<
        seq< chseq<'a','b','c'>, expect< 3, chseq<'d'> > >,
        handler
    > start;
  
    std::string text("abcD");
    PSTADE_CHECK( biscuit::match<start>(text) );
    PSTADE_CHECK( oven::equal(text, "abcd") );
}

// test_appendix
//
void test_appendix()
{
    typedef seq< chseq<'-','-'>, star_before< any, eol > > haskell_comment;

    PSTADE_CHECK((
        oven::equal(
            biscuit::parse<haskell_comment>("-- C++ also is functional.\nqsort [] = []"|oven::as_literal),
            "-- C++ also is functional."
        )
    ));
}

struct eternal : biscuit::identity<eternal>
{ };


int main()
{
    pstade::check_reset_ostream(std::cout);

    test_introduction();
    test_quick_start();
    test_actor();
    test_match();
    test_search();
    test_iterate();
    test_filter_range();
    test_token_range();
    test_capturing();
    test_valseq();
    test_valset();
    test_seq_range();
    test_set_range();
    test_error_handling();
    test_appendix();

    return 0;
}

