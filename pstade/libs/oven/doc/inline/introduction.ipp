std::vector<char> out;

BOOST_FOREACH (char ch,
    new std::string("!ExGNxxAR ,xOLxLExH")
        | shared
        | filtered(lambda::_1 != 'x')
        | regularized
        | reversed
        | transformed(to_lower)
        | memoized
) {
    out.push_back(ch);
}

BOOST_CHECK( oven::equals(out, "hello, range!"|as_literal) );