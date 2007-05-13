int answer[] = { 1,2,4,8,16 };
BOOST_CHECK( oven::equals(answer,
    oven::iteration(1, regular(lambda::_1 * 2))|oven::taken(5)
) );