std::map<int, std::string> m;
m[12] = "hello";
m[4]  = "map";
m[99] = "keys";

BOOST_FOREACH (int k, m|map_keys) {
    BOOST_CHECK( k != 12 || m[k] == "hello" );
    BOOST_CHECK( k != 4  || m[k] == "map" );
    BOOST_CHECK( k != 99 || m[k] == "keys" );
}