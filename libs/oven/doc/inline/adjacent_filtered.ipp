int src[] = { 2, 2, 4, 4, 6, 8, 8, 10, 10, 20, 40, 80, 120 };
int answer[] = { 2, 6, 8, 10, 120 };

BOOST_CHECK( oven::equals(
    src|adjacent_filtered(::not_divisor()),
    answer
) );