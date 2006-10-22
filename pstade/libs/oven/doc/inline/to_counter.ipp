int const rng[] = { 0,0,1,1,2,3,3,3,4,4,4,4,4,5,5 };
int i = oven::copy(rng|uniqued, oven::to_counter(0))|to_base;
BOOST_CHECK( i == 6 );

BOOST_CHECK( 7 == oven::adaptor_to<int>(oven::unique_copy(rng, oven::to_counter(1))) );