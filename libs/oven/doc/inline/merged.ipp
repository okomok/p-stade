std::string A1("abbbfH");
std::string A2("ABbCDFFhh");
std::string AA("aAbbbBbCDfFFHhh");
BOOST_CHECK( oven::equals(A1|merged(A2, &::lt_nocase), AA) );