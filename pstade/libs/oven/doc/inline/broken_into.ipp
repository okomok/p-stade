int const offsets[] = { 2,2,4 };
std::string src("12252001");
std::vector<std::string> ans; {
    ans.push_back("12");
    ans.push_back("25");
    ans.push_back("2001");
}

BOOST_CHECK( oven::equals(
    ans,
    src|broken_into<std::string>(boost::offset_separator(offsets, offsets+3))
) );