int const src[] = { 1,2,3,4,5 };
std::string null;

BOOST_FOREACH (std::string str, src|scanned(null, &::stringize)) {
    std::cout << "\"" << str << "\" ";
}
// outputs: "" "1" "12" "123" "1234" "12345"