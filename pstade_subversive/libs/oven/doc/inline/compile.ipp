std::string       rng1("12");
std::list<char>   rng2 = std::string("34")|copied;
std::vector<char> rng3 = std::string("56")|copied;

BOOST_CHECK( equals(
    compile( +(rng1 >> (rng2|as_term) >> rng3) ) | taken(17),
    std::string("12345612345612345")
) );