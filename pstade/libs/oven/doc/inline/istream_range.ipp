std::string result;
std::stringstream ss;
ss << "hello,istream_range!";
oven::copy(oven::make_istream_range<char>(ss), std::back_inserter(result));
BOOST_CHECK( oven::equals(result, std::string("hello,istream_range!")) );