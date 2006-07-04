std::string str("hello, array_range!");
array_range<char> arr(oven::distance(str));
str|copied(arr);
BOOST_CHECK( oven::equals(str, arr) );