int const ans[] = { 1,5,3,6,1,3,7,1,4,2,2 };
std::vector<int> vec = initial_values(1,5,3,6,1,3,7,1,4,2,2);
BOOST_CHECK( equals(vec, ans) );