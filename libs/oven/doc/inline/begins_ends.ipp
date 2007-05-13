std::string src("abcDefg");   
oven::copy(src|reversed|transformed(to_upper), src|reversed|begins);
BOOST_CHECK( oven::equals(src, std::string("ABCDEFG")) );