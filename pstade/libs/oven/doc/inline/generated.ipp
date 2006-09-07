BOOST_FOREACH (long x, oven::int_range(0, 100)|generated(&rand)) {
    std::cout << x << std::endl;
}