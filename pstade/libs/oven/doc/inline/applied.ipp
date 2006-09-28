std::string src("abcdefghijk");
namespace ph = boost::phoenix;
{
    std::string s1("efg");
    BOOST_CHECK((
        oven::equals(
            std::string("efghijk"),
            src|applied(ph::search(rng1, s1), oven::end)
        )
    ));
}