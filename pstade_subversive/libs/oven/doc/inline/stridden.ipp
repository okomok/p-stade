int const answer[] = { 2,6,10,14 };
BOOST_CHECK( oven::equals(answer,
    oven::make_counting_range(0, 16)|stridden(4, 2)
) );