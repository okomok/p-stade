std::list<char> lst;
oven::copy(std::string("cfbadehg"), std::back_inserter(lst));

oven::sort(lst|outplaced);
BOOST_CHECK( oven::equals(lst, std::string("abcdefgh")) );