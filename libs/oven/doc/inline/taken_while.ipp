std::string src("11111234516313!");

BOOST_CHECK( oven::equals(
    src|taken_while(lambda::_1 == '1'),
    std::string("11111")
) );