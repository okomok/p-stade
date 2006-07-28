std::string stringize(std::string const& state, int i)
{
    return state + boost::lexical_cast<std::string>(i);
}

void test()
{
    int const src[] = { 1,2,3,4,5 };

    BOOST_FOREACH (std::string str, src|scanned(std::string(), ::stringize)) {
        std::cout << "\"" << str << "\" ";
    }
    // outputs: "1" "12" "123" "1234" "12345"
}