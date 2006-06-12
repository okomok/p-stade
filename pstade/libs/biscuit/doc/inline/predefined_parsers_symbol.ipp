PSTADE_BISCUIT_SYMBOL(hello, "hello")
PSTADE_BISCUIT_SYMBOL(bye, "bye")

void test()
{
    BOOST_CHECK( biscuit::match<hello>("hello"|oven::null_terminated) );
    BOOST_CHECK( biscuit::match<bye>("bye"|oven::null_terminated) );
}