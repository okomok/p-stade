BOOST_CHECK( oven::equals(
    std::string("labor")
        | jointed(std::string("will be"))
        | constants("lost"),
    std::string("lost")
) );