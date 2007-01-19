BOOST_CHECK( equals(
    std::string("abcde")|transformed(as_single)|
        delimited("--"|as_literal)|dropped(2),
    std::string("a--b--c--d--e")
) );