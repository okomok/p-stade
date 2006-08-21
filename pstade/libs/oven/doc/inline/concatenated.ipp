std::string input("This is his face");
boost::regex re("\\w+");
BOOST_CHECK( oven::equals(
    input|tokenized(re)|concatenated,
    std::string("Thisishisface")
) );