BOOST_CHECK( oven::equals(
    std::string("hello, dropped!")|dropped(7),
    std::string("dropped!")
) );