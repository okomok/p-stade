std::string src("axaxaxbxbxbx");
std::string snapshot;
std::string answer("bbb");

BOOST_CHECK( oven::equals(
    src
        | filtered(lambda::_1 != 'x')
        | copied(std::back_inserter(snapshot))
        | filtered(lambda::_1 != 'a'),
    answer
) );

BOOST_CHECK( snapshot == "aaabbb" );