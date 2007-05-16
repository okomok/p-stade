std::string const str("gefadcb");
std::string const answer("abcdefg");

std::vector<std::string::const_iterator> iters;
oven::copy(str|directed, std::back_inserter(iters));
oven::sort( iters, boost::make_indirect_fun(::less_than()) );

BOOST_CHECK( oven::equals(iters|indirected, answer) );