namespace lambda = boost::lambda;
std::string src("abcdefghijk");
std::string s1("efg");
BOOST_CHECK((
	oven::equals(
		std::string("efghijk"),
		src|applied(lambda::bind(oven::search, lambda::_1, s1), oven::end)
	)
));