std::string pattern("ab");
BOOST_CHECK(( biscuit::match< seq< chseq<'x'>, set_range<pattern_loader>, chseq<'y'> > >("xay"|oven::as_c_str, pattern) ));
BOOST_CHECK(( biscuit::match< seq< chseq<'x'>, set_range<pattern_loader>, chseq<'y'> > >("xby"|oven::as_c_str, pattern) ));
BOOST_CHECK(( biscuit::match< seq< chseq<'x'>, set_range<pattern_loader>, chseq<'y'> > >("xcy"|oven::as_c_str, pattern) ));
