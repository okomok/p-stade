BOOST_CHECK( oven::equals(
    std::string("xyz")|cycled(3),
    std::string("xyzxyzxyz")
) );
