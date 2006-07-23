void test()
{
    int y = 5;

    boost::result_of< ::multiply_fun(int, int) >::type
        result = ::multiply(3, y);

    BOOST_CHECK( result == 15 );
}