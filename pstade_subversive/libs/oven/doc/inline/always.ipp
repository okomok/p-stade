BOOST_CHECK( oven::equals(
    std::string("labor")
        | jointed(std::string("will be"))
        | always("lost"),
    std::string("lost")
) );