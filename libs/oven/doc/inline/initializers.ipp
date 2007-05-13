int const ans[] = { 1,5,3,6,1,3,7,1,4,2,2 };
std::vector<int> vec = initializers(1,5,3,6,1,3,7,1,4,2,2);
BOOST_CHECK( equals(vec, ans) );