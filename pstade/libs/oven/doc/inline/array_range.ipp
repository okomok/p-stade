std::string str("hello, array_range!");
boost::array<char, 19> sarr;
str|copied_to(sarr);
oven::array_range<char> darr(19);
str|copied_to(darr);

BOOST_CHECK( oven::equals(sarr, darr) );