std::string out;

BOOST_FOREACH (char ch,
    new std::string("!exgnxxar ,xolxlexh") |
        shared |
        filtered(lambda::_1 != 'x') |
        reversed
) {
    out.push_back(ch);
}

BOOST_CHECK( out == "hello, range!" );