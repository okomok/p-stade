std::vector<int> vec = oven::construct(oven::make_counting_range(3, 9));
vec.push_back(9);
BOOST_CHECK( oven::equals(vec, oven::make_counting_range(3, 10)) );