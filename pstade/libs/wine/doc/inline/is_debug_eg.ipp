struct release_impl
{
    void operator()()
    {
        BOOST_ASSERT(( !pstade::is_debug<>::value ));
    }
};

struct debug_impl
{
    void operator()()
    {
        BOOST_ASSERT(( pstade::is_debug<>::value ));
    }
};

void test_is_debug()
{
    using namespace boost::mpl;

    if_< not_< pstade::is_debug<> >,
        release_impl,
        debug_impl
    >::type()();
}