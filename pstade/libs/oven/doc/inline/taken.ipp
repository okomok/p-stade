std::string src("hello, take_range!");
std::string ans("hello");
BOOST_CHECK( oven::equals(src|taken(7)|taken(5), ans) );
