std::string const src("hello, point_range");
std::vector<char> vec;
vec.resize(oven::distance(src) + 1);
std::strcpy(boost::begin(vec|pointed), src.c_str());
BOOST_CHECK(( oven::equals(vec|null_terminated, src) ));