std::string str("hello, array_range!");
boost::array<char, 19> sarr;
str|copied(sarr);
oven::array_range<char> darr(19);
str|copied(darr);

BOOST_CHECK( oven::equals(sarr, darr) );