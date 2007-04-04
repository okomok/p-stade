BOOST_AUTO(factorials,
    expression(counting_from(1)|scanned(1, regular(lambda::_1 * lambda::_2))) );