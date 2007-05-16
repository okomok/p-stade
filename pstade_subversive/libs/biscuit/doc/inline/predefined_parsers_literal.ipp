PSTADE_BISCUIT_SEQ_LITERAL(hello, "hello")
PSTADE_BISCUIT_SEQ_LITERAL(bye, L"bye")

void test_literal()
{
    BOOST_CHECK( biscuit::match<hello>(std::string("hello")) );
    BOOST_CHECK( biscuit::match<bye>(std::wstring(L"bye")) );
}