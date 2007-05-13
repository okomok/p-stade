std::string str0("every range");
std::vector<char> str1 = std::string(" is")|copied;
std::list<char> str2 = std::string(" string!?")|copied;

BOOST_CHECK( oven::equals(
    str0|jointed(str1)|jointed(str2),
    std::string("every range is string!?")
) );