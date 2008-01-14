match_results<std::string> caps;
std::string text("abcxabcx");

BOOST_CHECK((
    biscuit::results_match<
        seq<
            capture< 1, star_before< any, char_<'x'> > >,
            char_<'x'>,
            capture< 2, backref<1> >,
            char_<'x'>
        >
    >(text, caps)
));

BOOST_CHECK( oven::equal(caps[1], "abc") );
boost::to_upper(caps[1]);
BOOST_CHECK( oven::equal(text, "ABCxabcx") );
boost::to_upper(caps[2]);
BOOST_CHECK( oven::equal(text, "ABCxABCx") );