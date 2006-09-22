#include <pstade/vodka/drink.hpp>
#include <boost/test/minimal.hpp>


// PStade.Oven
//
// Copyright Shunsuke Sogame 2005-2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <pstade/oven.hpp>


#include <locale>
#include <string>
#include <vector>
#include <boost/range.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/lambda/core.hpp>
#include <boost/lambda/lambda.hpp>
#include <boost/foreach.hpp>
#include <pstade/egg/function.hpp>


struct baby_to_lower
{
    template< class Unused, class CharT >
    struct apply : boost::remove_const<CharT>
    { };

    template< class Result, class CharT >
    Result call(CharT ch)
    {
        return std::tolower(ch, std::locale());
    }
};


PSTADE_EGG_FUNCTION(to_lower, baby_to_lower)


using namespace pstade;
using namespace oven;


void test_introduction()
{
    {
        using namespace boost;

        std::vector<char> out;

        BOOST_FOREACH (char ch,
            new std::string("!ExGNxxAR ,xOLxLExH")
                | shared
                | filtered(lambda::_1 != 'x')
                | regularized
                | reversed
                | transformed(::to_lower)
                | memoized
        ) {
            out.push_back(ch);
        }

        BOOST_CHECK( oven::equals(out, "hello, range!"|null_terminated) );
    }
}


void test_stl_algorithms()
{
    std::string str;

    // iterator-based
    str = "gfedcba";
    std::sort(str.begin(), str.end());
    BOOST_CHECK( str == "abcdefg" );
    
    // Oven range-based
    str = "gfedcba";
    oven::sort(str);
    BOOST_CHECK( str == "abcdefg" );
}


void test_copied()
{
    std::vector<int> vec = oven::make_counting_range(3, 9)|copied;
    vec.push_back(9);
    BOOST_CHECK( oven::equals(vec, oven::make_counting_range(3, 10)) );
}


void test_distance()
{
    std::string str("012345");
    BOOST_CHECK( oven::distance(str) == 6 );
}


void test_equals()
{
    std::string str("hello, equals");
    std::vector<char> vec = str|copied;
    BOOST_CHECK( oven::equals(str, vec) );
}


#include <boost/array.hpp>

void test_array_range()
{
    std::string str("hello, array_range!");
    boost::array<char, 19> sarr;
    oven::copy(str, sarr|begins);
    oven::array_range<char> darr(19);
    oven::copy(str, darr|begins);

    BOOST_CHECK( oven::equals(sarr, darr) );
}


void test_counting_range()
{
    int ints[] = { 2, 3, 4, 5, 6 };
    BOOST_CHECK( oven::equal(oven::make_counting_range(2, 7), ints) );
}


void test_directory_range()
{

}


void test_empty_range()
{
    BOOST_CHECK( boost::empty(empty_range<int>()) );
}


void test_file_range()
{

}


#include <iterator>

void test_istream_range()
{
    std::string src("hello,istream_range!");

    std::stringstream ss;
    ss << src;

    std::string result;
    oven::copy(oven::make_istream_range<char>(ss), std::back_inserter(result));

    BOOST_CHECK( oven::equals(result, src) );
}


void test_single_range()
{
    BOOST_CHECK( oven::equals(oven::make_single_range('a'), std::string("a")) );
}


struct not_divisor
{
    bool operator()(int x, int y) const
    { return (y % x) != 0; }
};

void test_adjacent_filtered()
{
    int src[] = { 2, 2, 4, 4, 6, 8, 8, 10, 10, 20, 40, 80, 120 };
    int answer[] = { 2, 6, 8, 10, 120 };

    BOOST_CHECK( oven::equals(
        src|adjacent_filtered(::not_divisor()),
        answer
    ) );
}



void test_appended()
{
    std::string const str("hello, appen");

    BOOST_CHECK( oven::equals(
        str|appended('d')|appended('e')|appended('d')|appended('!'),
        std::string("hello, appended!")
    ) );
}


struct find
{
    typedef char result_type;

    char operator()(char ch) const
    {
        return std::toupper(ch, std::locale());
    }
};


void test_applied()
{

}


void test_array_protected()
{

}


void test_checked()
{
    std::string in("012345");
    std::string out("01234");

    try {
        oven::copy(in, boost::begin(out|checked));
    }
    catch (check_error const& ) {
        return;
    }

    BOOST_CHECK(false);
}


void test_cleared()
{
    BOOST_CHECK( boost::empty(
        std::string("labor")
            | jointed(std::string("lost"))
            | cleared
    ) );
}


void test_always()
{
    BOOST_CHECK( oven::equals(
        std::string("labor")
            | jointed(std::string("will be"))
            | always("lost"),
        std::string("lost")
    ) );
}


void test_copied_as_adaptor()
{
    using namespace boost;

    std::string src("axaxaxbxbxbx");
    std::string snapshot;
    std::string answer("bbb");

    BOOST_CHECK( oven::equals(
        src
            | filtered(lambda::_1 != 'x')
            | regularized
            | copied_out(std::back_inserter(snapshot))
            | filtered(lambda::_1 != 'a')
            | regularized,
        answer
    ) );

    BOOST_CHECK( snapshot == "aaabbb" );
}


struct less_than
{
    typedef bool result_type;

    template< class T >
    bool operator()(T& x, T& y) const
    {
        return x < y;
    }
};


void test_directed()
{
    using namespace boost;

    std::string const str("gefadcb");
    std::string const answer("abcdefg");

    std::vector<std::string::const_iterator> iters;
    oven::copy(str|directed, std::back_inserter(iters));
    oven::sort( iters, boost::make_indirect_fun(::less_than()) );

    BOOST_CHECK( oven::equals(iters|indirected, answer) );
}


void test_dropped()
{
    BOOST_CHECK( oven::equals(
        std::string("hello, dropped!")|dropped(7),
        std::string("dropped!")
    ) );
}


void test_filtered()
{
    using namespace boost;

    int src[]    = { 2,5,2,6,1,3,2 };
    int answer[] = { 0,5,0,6,1,3,0 };

    BOOST_FOREACH (int& i, src|filtered(lambda::_1 == 2)|regularized) {
        i = 0;
    }

    BOOST_CHECK( oven::equals(answer, src) );
}


void test_identities()
{
    BOOST_CHECK( oven::equals(
        std::string("hello, identities!")|identities,
        std::string("hello, identities!")
    ) );
}


void test_indirected()
{
    int src[]    = { 1,2,0,4,5 };
    int answer[] = { 1,2,3,4,5 };
    int *ptrs[]  = {&src[0],&src[1],&src[2],&src[3],&src[4]};

    BOOST_FOREACH (int& i, ptrs|indirected) {
        if (i == 0)
            i = 3;
    }

    BOOST_CHECK( oven::equals(src, answer) );
}


#include <map>

void test_map_keys()
{
    std::map<int, std::string> m;
    m[12] = "hello";
    m[4]  = "map";
    m[99] = "keys";

    BOOST_FOREACH (int k, m|map_keys) {
        BOOST_CHECK( k != 12 || m[k] == "hello" );
        BOOST_CHECK( k != 4  || m[k] == "map" );
        BOOST_CHECK( k != 99 || m[k] == "keys" );
    }
}


void test_map_values()
{
    std::map<int, std::string> m;
    m[12] = "hello";
    m[4]  = "map";
    m[99] = "keys";

    BOOST_FOREACH (std::string& v, m|map_values) {
        if (v == "keys")
            v = "values";
    }

    BOOST_CHECK( m[12] == "hello" );
    BOOST_CHECK( m[4]  == "map" );
    BOOST_CHECK( m[99] == "values" );
}


template< class Range >
void very_complicated_algorithm(Range const&)
{ }

void test_memoized()
{
    std::stringstream ss;
    ss << "hello, memoized!";

    ::very_complicated_algorithm(
        oven::make_istream_range<char>(ss)
            | memoized
            | directed
            | indirected
            | sorted
            | memoized
    );
}


#include <boost/algorithm/string.hpp>

void test_string_found()
{
#if !defined(BOOST_MSVC) // ICE under VC7.1/8
    std::string src("abc-*-ABC-*-aBc");
    namespace algo = boost::algorithm;

    int i = 0;
    BOOST_FOREACH (
        boost::sub_range<std::string> rng,
        src|string_found(algo::first_finder(std::string("abc"), algo::is_iequal())) )
    {
        if (i == 0)
            BOOST_CHECK( oven::equals(rng, std::string("abc")) );
        else if (i == 1)
            BOOST_CHECK( oven::equals(rng, std::string("ABC")) );
        else if (i == 2)
            BOOST_CHECK( oven::equals(rng, std::string("aBc")) );

        ++i;
    }
#endif
}


#include <vector>
#include <list>

void test_jointed()
{
    std::string str0("every range");
    std::vector<char> str1 = std::string(" is")|copied;
    std::list<char> str2 = std::string(" string!?")|copied;

    BOOST_CHECK( oven::equals(
        str0|jointed(str1)|jointed(str2),
        std::string("every range is string!?")
    ) );
}


int test_main(int, char*[])
{
    ::test_introduction();

    ::test_stl_algorithms();
    ::test_copied();
    ::test_distance();
    ::test_equals();

    ::test_array_range();
    ::test_counting_range();
    ::test_directory_range();
    ::test_empty_range();
    ::test_istream_range();
    ::test_single_range();

    ::test_adjacent_filtered();
    ::test_appended();
    ::test_applied();
    ::test_array_protected();
    ::test_checked();
    ::test_cleared();
    ::test_always();
    ::test_copied_as_adaptor();
    ::test_directed();
    ::test_dropped();
    ::test_filtered();
    ::test_identities();
    ::test_indirected();
    ::test_map_keys();
    ::test_map_values();
    ::test_memoized();

    ::test_jointed();
    ::test_string_found();

    return 0;
}
