std::string src("cjaigvwzenqhe");
std::string::iterator it = oven::adapted_to<std::string::iterator>(
    oven::max_element(
        src
            | filtered(regular(lambda::_1 != 'z'))
            | filtered(regular(lambda::_1 != 'w'))
    )
);

BOOST_CHECK( *it == 'v' );