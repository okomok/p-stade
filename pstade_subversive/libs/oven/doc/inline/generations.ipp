BOOST_FOREACH (long x, oven::from_0_to(100)|generations(&rand)) {
    std::cout << x << std::endl;
}