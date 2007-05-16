std::vector<char> vec;
oven::copy(file_range<char>("data.txt"), std::back_inserter(vec));