std::string text("  /* c comment no.1 */int i; /* c comment no.2 */i = 1; /* c comment no.3 */ ++i;  ");
token_range<c_comment, std::string> comments(text);
BOOST_FOREACH (boost::sub_range<std::string> rng, comments) {
    std::cout << boost::copy_range<std::string>(rng) << std::endl;
}

BOOST_FOREACH (
    boost::iterator_range<const char *> rng,
    "  /* c comment no.1 */int i; /* c comment no.2 */i = 1; /* c comment no.3 */ ++i;  " |
        oven::null_terminated |
        biscuit::tokenized<c_comment>()
) {
    std::cout << boost::copy_range<std::string>(rng) << std::endl;
}