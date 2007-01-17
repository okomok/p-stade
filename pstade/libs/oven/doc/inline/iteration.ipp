int answer[] = { 1,2,4,8,16 };
BOOST_CHECK( oven::equals(answer,
    oven::iteration(1, lambda::_1 * 2)|regularized|oven::taken(5)
) );