BOOST_CHECK( oven::equals(
    std::string("xyz")|cycled(0, 3),
    std::string("xyzxyzxyz")
) );
