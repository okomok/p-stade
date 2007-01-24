std::string rng("hello! any_range!");
any_range<char const&, boost::bidirectional_traversal_tag> any_ =
    rng|transformed(to_upper)|const_lvalues|filtered(lambda::_1 != '!')|regularized;

BOOST_CHECK( oven::equals(any_, std::string("HELLO ANY_RANGE")) );