struct handler
{
    template< class State, class UserState >
    error_status operator()(State&, UserState&, boost::sub_range<std::string> rng, int id)
    {
        BOOST_CHECK( id == 3 );
        boost::to_lower(rng);
        std::cout << "exception caught...Test concluded successfully" << std::endl;
        return error_retry;
    }
};

void test_error_handling()
{
    typedef guard<
        seq< chseq<'a','b','c'>, expect< 3, chseq<'d'> > >,
        handler
    > start;
  
    std::string text("abcD");
    BOOST_CHECK( biscuit::match<start>(text) );
    BOOST_CHECK( oven::equal(text, "abcd") );
}