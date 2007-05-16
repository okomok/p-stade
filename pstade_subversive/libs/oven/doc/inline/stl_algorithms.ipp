std::string str;

// iterator-based
str = "gfedcba";
std::sort(str.begin(), str.end());
BOOST_CHECK( str == "abcdefg" );

// Oven range-based
str = "gfedcba";
oven::sort(str);
BOOST_CHECK( str == "abcdefg" );