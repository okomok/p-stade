std::vector<int> vec = oven::make_count_range(3, 9)|copied;
vec.push_back(9);
BOOST_CHECK( oven::equals(vec, oven::make_count_range(3, 10)) );