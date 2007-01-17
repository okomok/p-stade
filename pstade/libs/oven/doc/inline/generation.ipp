struct rand_generator
{
    typedef boost::optional<long> result_type;

    result_type operator()()
    {
        long result = std::rand();
        if (result % 3 == 0)
            return result_type(); // range is end.

        return result;
    }
};

void test()
{
    rand_generator X;
    BOOST_FOREACH (long x, oven::generation(X)) {
        std::cout << x << std::endl;
    }
}