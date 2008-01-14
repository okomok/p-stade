struct pattern_loader
{
    std::string& operator()(std::string& pattern)
    {
        pattern += "c";
        return pattern;
    }
};

void test_seq_range()
{
    std::string pattern("ab");
    BOOST_CHECK(( biscuit::match< seq< chseq<'x'>, seq_range<pattern_loader>, chseq<'y'> > >("xabcy"|oven::as_c_str, pattern) ));
}