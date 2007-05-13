std::string src("cjaigvwzenqhe");
std::string::iterator it = oven::adaptor_to<std::string::iterator>(
    oven::max_element(
        src
            | filtered(lambda::_1 != 'z')
            | regularized
            | filtered(lambda::_1 != 'w')
            | regularized
    )
);

BOOST_CHECK( *it == 'v' );