any_range<int, boost::single_pass_traversal_tag> factorials =
    counting_from(1) |
        scanned(1, regular(lambda::_1 * lambda::_2));