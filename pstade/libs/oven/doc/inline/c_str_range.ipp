{
    c_str_range<char const> rng("hello\0range");
    BOOST_CHECK( oven::equals(rng, std::string("hello")) );
}
{
    wchar_t const *psz = L"hello range";
    BOOST_CHECK( oven::equals(psz|as_c_str, std::wstring(L"hello range")) );
}
{
    std::string src("hello range");
    BOOST_CHECK( oven::equals(src.c_str()|as_c_str, src) );
}