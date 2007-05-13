BOOST_CHECK( boost::empty(
    std::string("labor")
        | jointed(std::string("lost"))
        | cleared
) );