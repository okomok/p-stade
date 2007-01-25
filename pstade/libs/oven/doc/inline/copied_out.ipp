std::string src("axaxaxbxbxbx");
std::string snapshot;
std::string answer("bbb");

BOOST_CHECK( oven::equals(
    src
        | filtered(regular(lambda::_1 != 'x'))
        | copied_out(std::back_inserter(snapshot))
        | filtered(regular(lambda::_1 != 'a')),
    answer
) );

BOOST_CHECK( snapshot == "aaabbb" );