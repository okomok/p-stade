PSTADE_BISCUIT_SYMBOL(hello, "hello")
PSTADE_BISCUIT_SYMBOL(bye, L"bye")

void test_symbol()
{
    BOOST_CHECK( biscuit::match<hello>(std::string("hello")) );
    BOOST_CHECK( biscuit::match<bye>(std::wstring(L"bye")) );
}