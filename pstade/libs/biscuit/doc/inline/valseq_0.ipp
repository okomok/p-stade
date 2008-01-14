template< int i >
struct value_at
{
    std::string& operator()(std::vector<std::string>& values)
    {
        return values.at(i);
    }
};

void test_valseq()
{
    using namespace boost::assign;

    std::vector<std::string> inputs; { inputs += "ghi", "abc"; }
    std::vector<std::string> values; { values += "abc", "def", "ghi"; }
  
    BOOST_CHECK(( biscuit::match< valseq< value_at<2>, value_at<0> > >(inputs, values) ));
}