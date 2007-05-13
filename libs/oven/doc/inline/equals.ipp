std::string str("hello, equals");
std::vector<char> vec = str|copied;
BOOST_CHECK( oven::equals(str, vec) );