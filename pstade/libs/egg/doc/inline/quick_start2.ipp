void test()
{
    int y = 5;

    boost::result_of< ::op_multiply(int, int) >::type
        result = ::multiply(3, y);

    BOOST_CHECK( result == 15 );
}