int ans[] = { 2, 3, 4, 5, 6 };
BOOST_CHECK( oven::equal(counting(2, 7), ans) );

std::vector<int> vec;
BOOST_FOREACH (int i, counting(0, 5)) {
    vec.push_back(i);
}