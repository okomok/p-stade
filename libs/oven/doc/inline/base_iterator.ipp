std::string src("cjaigvwzenqhe");
std::string::const_iterator it = oven::base_iterator(
    oven::max_element(
        src
            | filtered(lambda::_1 != 'z')
            | filtered(lambda::_1 != 'w')
            | regularized // for non-assignability of lambda functors
    )
);

BOOST_CHECK( *it == 'v' );