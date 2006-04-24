struct pattern_loader :
    std::unary_function<std::string&, std::string&>
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
    BOOST_CHECK(( biscuit::match< seq< chseq<'x'>, seq_range<pattern_loader>, chseq<'y'> > >("xabcy"|oven::null_terminated, pattern) ));
}