int const answer[] = { 2,6,10,14 };
BOOST_CHECK( oven::equals(answer,
    oven::make_count_range(0, 16)|sliced(2, 4)
) );