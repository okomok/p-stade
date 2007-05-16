BOOST_FOREACH (long x, oven::from_0_to(100)|generated(&rand)) {
    std::cout << x << std::endl;
}