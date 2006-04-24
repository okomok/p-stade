std::string text("  int i; /* c comment */ int j; ");
boost::sub_range<std::string> rng = biscuit::search<c_comment>(text);
BOOST_CHECK( oven::equal(rng, "/* c comment */") );