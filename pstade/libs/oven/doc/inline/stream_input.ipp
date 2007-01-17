std::string src("hello,stream_input!");

std::stringstream ss;
ss << src;

std::string result;
oven::copy(oven::stream_input<char>(ss), std::back_inserter(result));

BOOST_CHECK( oven::equals(result, src) );