std::string text("  /* c comment no.1 */ int i; /* c comment no.2 */ i = 1; /* c comment no.3 */ ++i;  ");
filter_range<c_comment, std::string> comments(text);
BOOST_CHECK(( biscuit::match< repeat<c_comment, 3> >(comments) ));
