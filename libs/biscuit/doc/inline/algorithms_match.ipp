BOOST_CHECK( biscuit::match<xml_comment>("<!-- hello, xml comment -->"|oven::null_terminated) );
BOOST_CHECK( !biscuit::match<xml_comment>("<!-- not well-formed comment -- -->"|oven::null_terminated) );