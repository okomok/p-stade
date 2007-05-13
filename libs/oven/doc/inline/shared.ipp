BOOST_FOREACH (char ch, std::string("dangling")|identities) {
    // will crash; 'std::string' object doesn't exist anymore. 
    std::cout << ch;
}

BOOST_FOREACH (char ch, new std::string("ok")|shared|identities) {
    // works fine.
    std::cout << ch;
}