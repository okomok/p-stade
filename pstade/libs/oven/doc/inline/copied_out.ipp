std::string src("axaxaxbxbxbx");
std::string snapshot;
std::string answer("bbb");

BOOST_CHECK( oven::equals(
    src
        | filtered(lambda::_1 != 'x')
        | regularized
        | copied_out(std::back_inserter(snapshot))
        | filtered(lambda::_1 != 'a')
        | regularized,
    answer
) );

BOOST_CHECK( snapshot == "aaabbb" );