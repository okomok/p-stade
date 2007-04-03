std::string in("012345");
std::string out("01234");

try {
    oven::copy(in, boost::begin(out|checked));
}
catch (std::out_of_range const& ) {
    return;
}

BOOST_CHECK(false);