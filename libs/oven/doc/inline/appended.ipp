std::string const str("hello, appen");

BOOST_CHECK( oven::equals(
    str|appended('d')|appended('e')|appended('d')|appended('!'),
    std::string("hello, appended!")
) );