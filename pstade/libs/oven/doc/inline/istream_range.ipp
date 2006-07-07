std::string src("hello,istream_range!");

std::stringstream ss;
ss << src;

std::string result;
oven::copy(oven::make_istream_range<char>(ss), std::back_inserter(result));

BOOST_CHECK( oven::equals(result, src) );