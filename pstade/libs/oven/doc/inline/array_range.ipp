std::string str("hello, array_range!");
array_range<char> arr(oven::distance(str));
oven::copies(str, arr);
BOOST_CHECK( oven::equals(str, arr) );