std::string  in("hello,copies!");
std::string out("hello, utils!");
oven::copies(in, out);
BOOST_CHECK( oven::equals(in, out) );