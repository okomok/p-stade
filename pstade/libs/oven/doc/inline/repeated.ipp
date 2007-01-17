BOOST_CHECK( oven::equals(
	'A'|repeated(6),
	std::string("AAAAAA")
) );