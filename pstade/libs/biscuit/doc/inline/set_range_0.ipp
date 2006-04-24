std::string pattern("ab");
BOOST_CHECK(( biscuit::match< seq< chseq<'x'>, set_range<pattern_loader>, chseq<'y'> > >("xay"|oven::null_terminated, pattern) ));
BOOST_CHECK(( biscuit::match< seq< chseq<'x'>, set_range<pattern_loader>, chseq<'y'> > >("xby"|oven::null_terminated, pattern) ));
BOOST_CHECK(( biscuit::match< seq< chseq<'x'>, set_range<pattern_loader>, chseq<'y'> > >("xcy"|oven::null_terminated, pattern) ));
