BOOST_CHECK( oven::equals(
    std::string("abcde")|biscuit::tokenized<biscuit::any>()|
        delimited("--"|as_literal)|dropped(2),
    std::string("a--b--c--d--e")
) );