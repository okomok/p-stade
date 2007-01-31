int xs[]  = { 0, 1, 2, 3, 4, 5, 6 };
int ys[]  = { 1, 6, 1, 2, 7, 8, 3 };
int ans[] = { 1, 7, 3, 5,11,13, 9 };

BOOST_CHECK( oven::equals(
    boost::tie(xs, ys)|zipped_with(::plus()),
    ans
) );
