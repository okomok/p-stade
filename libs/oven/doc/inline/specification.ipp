std::string src("hello, specification");

boost::result_of<op_make_filtered(std::string&, bool(*)(char))>::type
    result = make_filtered(src, &is_upper);
BOOST_CHECK( equals(result, src|filtered(&is_upper)) );