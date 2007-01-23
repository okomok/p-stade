std::string str("hello, array_range!");
boost::array<char, 19> sarr;
oven::copy(str, sarr|begin);
oven::array_range<char> darr(19);
oven::copy(str, darr|begin);

BOOST_CHECK( oven::equals(sarr, darr) );