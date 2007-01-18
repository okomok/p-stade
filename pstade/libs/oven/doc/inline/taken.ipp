std::string src("hello, taken!");
std::string ans("hello");
BOOST_CHECK( oven::equals(src|taken(7)|taken(5), ans) );
