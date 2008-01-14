BOOST_CHECK( biscuit::match<xml_comment>("<!-- hello, xml comment -->"|oven::as_c_str) );
BOOST_CHECK( !biscuit::match<xml_comment>("<!-- not well-formed comment -- -->"|oven::as_c_str) );