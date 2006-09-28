{
    literal_range<char, 12> rng("hello range");
    BOOST_CHECK( oven::equals(rng, std::string("hello range")) );
}
{
    BOOST_CHECK( oven::equals("hello range"|as_literal, std::string("hello range")) );
}
{
    BOOST_CHECK( oven::equals(
        "hello\0range"|as_c_str,
        std::string("hello")
    ) );
    BOOST_CHECK( oven::equals(
        "hello\0range"|as_literal,
        std::string("hello")|jointed('\0'|as_single)|jointed(std::string("range"))
    ) );
}