std::string const src("hello, pointed");
std::vector<char> vec;
vec.resize(oven::distance(src) + 1);
std::strcpy(boost::begin(vec|pointed), src.c_str());
BOOST_CHECK(( oven::equals(vec|as_c_str, src) ));