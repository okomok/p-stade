std::map<int, std::string> m;
m[12] = "hello";
m[4]  = "map";
m[99] = "keys";

BOOST_FOREACH (std::string& v, m|map_values) {
    if (v == "keys")
        v = "values";
}

BOOST_CHECK( m[12] == "hello" );
BOOST_CHECK( m[4]  == "map" );
BOOST_CHECK( m[99] == "values" );