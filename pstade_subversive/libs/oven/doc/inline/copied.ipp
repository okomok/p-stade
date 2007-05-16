std::vector<int> vec = oven::counting(3, 9)|copied;
vec.push_back(9);
BOOST_CHECK( oven::equals(vec, oven::counting(3, 10)) );