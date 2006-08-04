void impl(boost::mpl::true_)
{
    BOOST_CHECK(( pstade::is_ndebug<>::value ));
    std::cout << "release mode";
}

void impl(boost::mpl::false_)
{
    BOOST_CHECK(( !pstade::is_ndebug<>::value ));
    std::cout << "debug mode";
}

void test()
{
    ::impl(pstade::is_ndebug<>());
}
