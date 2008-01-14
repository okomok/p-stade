std::vector<std::string> inputs0; { inputs0 += "abc"; }
std::vector<std::string> inputs1; { inputs1 += "def"; }
std::vector<std::string> inputs2; { inputs2 += "ghi"; }
std::vector<std::string> values; { values += "abc", "def", "ghi"; }

BOOST_CHECK(( biscuit::match< valset< value_at<0>, value_at<1>, value_at<2> > >(inputs0, values) ));
BOOST_CHECK(( biscuit::match< valset< value_at<0>, value_at<1>, value_at<2> > >(inputs1, values) ));
BOOST_CHECK(( biscuit::match< valset< value_at<0>, value_at<1>, value_at<2> > >(inputs2, values) ));
